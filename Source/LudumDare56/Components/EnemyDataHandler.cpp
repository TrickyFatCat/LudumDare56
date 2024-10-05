// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDataHandler.h"

#include "EnemyAttackComponent.h"
#include "EnemyMovementComponent.h"
#include "HitPointsComponent.h"
#include "LudumDare56/Enemies/EnemyPawn.h"


UEnemyDataHandler::UEnemyDataHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEnemyDataHandler::InitializeComponent()
{
	Super::InitializeComponent();

	if (!GetWorld()->IsGameWorld())
	{
		return;
	}

	if (!EnemyDataTable || !GetOwner()->IsA(AEnemyPawn::StaticClass()))
	{
		return;
	}

	TArray<FEnemyData*> EnemyData;
	EnemyDataTable->GetAllRows<FEnemyData>("", EnemyData);

	if (EnemyData.IsEmpty())
	{
		return;
	}

	auto Predicate = [&](const FEnemyData* TargetData)
	{
		return TargetData->EnemyClass == GetOwner()->GetClass();
	};

	FEnemyData* Data = *EnemyData.FindByPredicate(Predicate);

	if (!Data)
	{
		return;
	}

	UHitPointsComponent* HitPointsComponent = GetOwner()->GetComponentByClass<UHitPointsComponent>();

	if (IsValid(HitPointsComponent))
	{
		HitPointsComponent->SetMaxHitPoints(Data->HitPoints);
	}

	UEnemyMovementComponent* EnemyMovementComponent = GetOwner()->GetComponentByClass<UEnemyMovementComponent>();

	if (IsValid(EnemyMovementComponent))
	{
		EnemyMovementComponent->SetSpeed(Data->Speed);
	}

	UEnemyAttackComponent* AttackComponent = GetOwner()->GetComponentByClass<UEnemyAttackComponent>();
	AttackComponent->Range = Data->AttackRange;
	AttackComponent->Damage = Data->Damage;
	AttackComponent->ProjectilesPerAttack = Data->ProjectilesPerAttack;
	AttackComponent->AttackAngle = Data->AttackAngle;
	AttackComponent->AttackMontage = Data->AttackAnimMontage;
	AttackComponent->ProjectileClass = Data->ProjectileClass;
}
