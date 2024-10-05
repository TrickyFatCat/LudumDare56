// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyDeathComponent.h"


UEnemyDeathComponent::UEnemyDeathComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEnemyDeathComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	}
}

bool UEnemyDeathComponent::StartDeathSequence()
{
	if (!IsValid(DeathMontage))
	{
		return false;
	}

	SkeletalMeshComponent->PlayAnimation(DeathMontage, false);
	return true;
}
