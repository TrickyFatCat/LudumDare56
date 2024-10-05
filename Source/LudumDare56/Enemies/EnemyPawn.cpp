﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LudumDare56/Components/EnemyAttackComponent.h"
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
	EnemyAttackComponent = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("EnemyAttack"));
}

void AEnemyPawn::BeginPlay()
{
	const FVector PlayerLocation = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	SetActorRotation(NewRotation);
	EnemyStateControllerComponent->EnterIdleState();
	
	OnTakeAnyDamage.AddUniqueDynamic(this, &AEnemyPawn::HandleAnyDamageTaken);
	
	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->OnZeroHitPoints.AddUniqueDynamic(this, &AEnemyPawn::HandleZeroHitPoints);
	}

	EnemyStateControllerComponent->OnStateChanged.AddUniqueDynamic(this, &AEnemyPawn::HandleEnemyStateChanged);
	Super::BeginPlay();
}

void AEnemyPawn::HandleEnemyStateChanged(UEnemyStateControllerComponent* Component, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::Idle:
		SkeletalMeshComponent->PlayAnimation(IdleMontage, true);
		break;
		
	case EEnemyState::Chase:
		EnemyMovementComponent->Activate(false);
		SkeletalMeshComponent->PlayAnimation(MovementMontage, true);
		break;

	case EEnemyState::Attack:
		EnemyAttackComponent->StartAttack();
		break;

	case EEnemyState::Death:
		EnemyMovementComponent->Deactivate();
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
