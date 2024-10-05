// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LudumDare56/Components/EnemyDataHandler.h"
#include "LudumDare56/Components/EnemyDeathComponent.h"
#include "LudumDare56/Components/EnemyExperienceComponent.h"
#include "LudumDare56/Components/EnemyMovementComponent.h"
#include "LudumDare56/Components/EnemyStateControllerComponent.h"
#include "LudumDare56/Components/HitPointsComponent.h"


AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(GetRootComponent());

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>(TEXT("HitPointsComponent"));
	EnemyStateControllerComponent = CreateDefaultSubobject<
		UEnemyStateControllerComponent>(TEXT("EnemyStateController"));
	EnemyMovementComponent = CreateDefaultSubobject<UEnemyMovementComponent>(TEXT("EnemyMovement"));
	EnemyExperienceComponent = CreateDefaultSubobject<UEnemyExperienceComponent>(TEXT("EnemyExperience"));
	EnemyDeathComponent = CreateDefaultSubobject<UEnemyDeathComponent>(TEXT("DeathComponent"));
	EnemyDataHandler = CreateDefaultSubobject<UEnemyDataHandler>(TEXT("DataHandler"));
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	const FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	SetActorRotation(NewRotation);
}

void AEnemyPawn::HandleEnemyStateChanged(UEnemyStateControllerComponent* Component, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::Chase:
		EnemyMovementComponent->Activate(false);
		break;

	case EEnemyState::Death:
		EnemyDeathComponent->StartDeathSequence();
		break;

	default:
		EnemyMovementComponent->Deactivate();
		break;
	}
}

void AEnemyPawn::HandleAnyDamageTaken(AActor* DamagedActor,
                                      float Damage,
                                      const UDamageType* DamageType,
                                      AController* InstigatedBy,
                                      AActor* DamageCauser)
{
	HitPointsComponent->DecreaseHitPoints(Damage);
}

void AEnemyPawn::HandleZeroHitPoints(UHitPointsComponent* Component)
{
	EnemyStateControllerComponent->EnterDeathState();
	EnemyExperienceComponent->GiveExperience();
}
