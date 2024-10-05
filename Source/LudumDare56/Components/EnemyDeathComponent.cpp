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
		USkeletalMeshComponent* SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(SkeletalMeshComponent))
		{
			AnimInstance = SkeletalMeshComponent->GetAnimInstance();
		}
	}
}

bool UEnemyDeathComponent::StartDeathSequence()
{
	if (!IsValid(AnimInstance) && !IsValid(DeathMontage))
	{
		return false;
	}

	AnimInstance->Montage_Play(DeathMontage);
	return true;
}
