// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LudumDare56/Components/DistanceCheckComponent.h"
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
	DistanceCheckComponent = CreateDefaultSubobject<UDistanceCheckComponent>(TEXT("DistanceCheck"));
}

void AEnemyPawn::BeginPlay()
{
	const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerLocation);
	NewRotation.Pitch = 0.f;
	NewRotation.Roll = 0.f;
	SetActorRotation(NewRotation);

	DistanceCheckComponent->TargetLocation = PlayerLocation;
	DistanceCheckComponent->TargetDistance = EnemyAttackComponent->Range;
	DistanceCheckComponent->OnEnterTargetRange.AddUniqueDynamic(this, &AEnemyPawn::HandleEnterAttackRange);
	DistanceCheckComponent->OnExitTargetRange.AddUniqueDynamic(this, &AEnemyPawn::HandleExitAttackRange);
	
	OnTakeAnyDamage.AddUniqueDynamic(this, &AEnemyPawn::HandleAnyDamageTaken);

	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->OnZeroHitPoints.AddUniqueDynamic(this, &AEnemyPawn::HandleZeroHitPoints);
	}

	EnemyStateControllerComponent->OnStateChanged.AddUniqueDynamic(this, &AEnemyPawn::HandleEnemyStateChanged);
	EnemyStateControllerComponent->EnterChaseState();
	Super::BeginPlay();
}

bool AEnemyPawn::ApplyStun(const float Duration)
{
	return EnemyStateControllerComponent->EnterStunState(Duration);
}

void AEnemyPawn::HandleEnemyStateChanged(UEnemyStateControllerComponent* Component, EEnemyState NewState)
{
	switch (NewState)
	{
	case EEnemyState::Idle:
		SkeletalMeshComponent->PlayAnimation(IdleMontage, true);
		DistanceCheckComponent->Activate(false);
		break;

	case EEnemyState::Chase:
		EnemyMovementComponent->Activate(false);
		DistanceCheckComponent->Activate(false);
		SkeletalMeshComponent->PlayAnimation(MovementMontage, true);
		break;

	case EEnemyState::Attack:
		DistanceCheckComponent->Deactivate();
		EnemyMovementComponent->Deactivate();
		EnemyAttackComponent->StartAttack();
		break;

	case EEnemyState::Death:
		DistanceCheckComponent->Deactivate();
		EnemyMovementComponent->Deactivate();
		EnemyDeathComponent->StartDeathSequence();
		break;

	case EEnemyState::Stun:
		SkeletalMeshComponent->PlayAnimation(IdleMontage, true);
		DistanceCheckComponent->Deactivate();
		EnemyMovementComponent->Deactivate();
		break;

	default:
		DistanceCheckComponent->Deactivate();
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
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyPawn::HandleEnterAttackRange(UDistanceCheckComponent* Component)
{
	EnemyStateControllerComponent->EnterAttackState();
}

void AEnemyPawn::HandleExitAttackRange(UDistanceCheckComponent* Component)
{
	EnemyStateControllerComponent->EnterChaseState();
}
