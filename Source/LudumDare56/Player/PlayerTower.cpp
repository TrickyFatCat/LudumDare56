// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTower.h"

#include "TrickyGameModeBase.h"
#include "TrickyGameModeLibrary.h"
#include "LudumDare56/Components/HitPointsComponent.h"
#include "LudumDare56/Components/HitPointsRegenerationComponent.h"
#include "LudumDare56/Components/PlayerLevelComponent.h"


APlayerTower::APlayerTower()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>(TEXT("HitPoints"));
	PlayerLevelComponent = CreateDefaultSubobject<UPlayerLevelComponent>(TEXT("PlayerLevel"));
	HitPointsRegenerationComponent = CreateDefaultSubobject<UHitPointsRegenerationComponent>(TEXT("HitPointsRegeneration"));
}

void APlayerTower::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddUniqueDynamic(this, &APlayerTower::HandleAnyDamageTaken);

	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->OnZeroHitPoints.AddUniqueDynamic(this, &APlayerTower::HandleZeroHitPoints);
	}
}

void APlayerTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerTower::HandleAnyDamageTaken(AActor* DamagedActor,
                                        float Damage,
                                        const UDamageType* DamageType,
                                        AController* InstigatedBy,
                                        AActor* DamageCauser)
{
	HitPointsComponent->DecreaseHitPoints(Damage);
}

void APlayerTower::HandleZeroHitPoints(UHitPointsComponent* Component)
{
	ATrickyGameModeBase* GameMode = UTrickyGameModeLibrary::GetTrickyGameMode(this);

	if (IsValid(GameMode))
	{
		GameMode->FinishSession(false);
	}
}
