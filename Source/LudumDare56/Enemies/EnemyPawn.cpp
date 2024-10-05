// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "MovieSceneSequenceID.h"
#include "Components/CapsuleComponent.h"
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
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyPawn::HandleEnemyStateChanged(UEnemyStateControllerComponent* Component, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::Chase:
		EnemyMovementComponent->Activate();
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
}
