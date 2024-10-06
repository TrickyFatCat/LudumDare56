// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnController.h"

#include "EnemyPawn.h"
#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "LudumDare56/Components/HitPointsComponent.h"
#include "LudumDare56/Components/PlayerLevelComponent.h"


AEnemySpawnController::AEnemySpawnController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawnController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (IsValid(PlayerPawn))
	{
		UPlayerLevelComponent* PlayerLevelComponent = PlayerPawn->GetComponentByClass<UPlayerLevelComponent>();

		if (IsValid(PlayerLevelComponent))
		{
			PlayerLevelComponent->OnLevelIncreased.AddUniqueDynamic(this,
			                                                        &AEnemySpawnController::HandlePlayerLevelIncreased);
		}
	}

	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->OnStateChanged.AddUniqueDynamic(this, &AEnemySpawnController::HandleGameStateChanged);
	}

	SetSpawnData();
	StartSpawn();
}

void AEnemySpawnController::StopSpawn()
{
	if (SpawnData.IsEmpty())
	{
		return;
	}

	for (auto Data : SpawnData)
	{
		GetWorldTimerManager().ClearTimer(Data.SpawnTimerHandle);
	}
}

void AEnemySpawnController::ProcessEnemySpawn(TSubclassOf<AEnemyPawn> EnemyClass)
{
	auto Predicate = [&](FEnemySpawnData TargetData)
	{
		return TargetData.Enemy == EnemyClass;
	};

	FEnemySpawnData* Data = SpawnData.FindByPredicate(Predicate);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &AEnemySpawnController::ProcessEnemySpawn, Data->Enemy);
	GetWorldTimerManager().SetTimer(Data->SpawnTimerHandle,
	                                TimerDelegate,
	                                Data->SpawnDelay.GetValueAtLevel(CurrentLevel),
	                                false);

	const int32 MaxNum = Data->MaxNumber.GetValueAtLevel(CurrentLevel);

	if (MaxNum <= 0 || Data->CurrentNumber >= MaxNum)
	{
		return;
	}

	if (!SpawnEnemy(Data->Enemy))
	{
		return;
	}

	Data->CurrentNumber++;
}

void AEnemySpawnController::SetSpawnData()
{
	if (!EnemySpawnDataTable)
	{
		return;
	}

	SpawnData.Empty();
	TArray<FEnemySpawnData*> DataArray;
	EnemySpawnDataTable->GetAllRows("", DataArray);

	for (const auto Data : DataArray)
	{
		SpawnData.Add(*Data);
	}
}

void AEnemySpawnController::StartSpawn()
{
	if (SpawnData.IsEmpty())
	{
		return;
	}

	for (auto Data : SpawnData)
	{
		if (!IsValid(Data.Enemy))
		{
			continue;
		}

		ProcessEnemySpawn(Data.Enemy);
	}
}

bool AEnemySpawnController::SpawnEnemy(TSubclassOf<AEnemyPawn> EnemyClass)
{
	if (!IsValid(EnemyClass))
	{
		return false;
	}

	FTransform SpawnTransform = FTransform::Identity;
	const FVector SpawnLocation = SpawnLocations.IsEmpty()
		                              ? GetActorLocation()
		                              : SpawnLocations[FMath::RandRange(0, SpawnLocations.Num() - 1)];
	SpawnTransform.SetLocation(SpawnLocation);

	AEnemyPawn* NewEnemy = GetWorld()->SpawnActorDeferred<AEnemyPawn>(EnemyClass, SpawnTransform);
	UHitPointsComponent* HitPointsComponent = NewEnemy->GetComponentByClass<UHitPointsComponent>();

	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->OnZeroHitPoints.AddUniqueDynamic(this, &AEnemySpawnController::HandleEnemyDeath);
	}

	NewEnemy->FinishSpawning(SpawnTransform);
	return true;
}

void AEnemySpawnController::HandleEnemyDeath(UHitPointsComponent* Component)
{
	auto Predicate = [&](FEnemySpawnData TargetData)
	{
		return TargetData.Enemy == Component->GetOwner()->GetClass();
	};

	FEnemySpawnData& Data = *SpawnData.FindByPredicate(Predicate);
	Data.CurrentNumber -= 1;
	Component->OnZeroHitPoints.RemoveDynamic(this, &AEnemySpawnController::HandleEnemyDeath);
}

void AEnemySpawnController::HandlePlayerLevelIncreased(UPlayerLevelComponent* Component, int32 NewLevel)
{
	CurrentLevel = NewLevel;
}

void AEnemySpawnController::HandleGameStateChanged(EGameModeState NewState)
{
	if (NewState == EGameModeState::Lose || NewState == EGameModeState::Win)
	{
		StopSpawn();
	}
}
