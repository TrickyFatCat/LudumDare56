// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityManagerComponent.h"

#include "LudumDare56/Player/Abilities/PlayerAbility.h"


UPlayerAbilityManagerComponent::UPlayerAbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerAbilityManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		if (AbilitiesClasses.IsEmpty())
		{
			return;
		}

		FTransform SpawnTransform = FTransform::Identity;
		Abilities.Empty();

		for (auto AbilityClass : AbilitiesClasses)
		{
			APlayerAbility* NewAbility = GetWorld()->SpawnActorDeferred<APlayerAbility>(AbilityClass, SpawnTransform);
			NewAbility->FinishSpawning(SpawnTransform);
			NewAbility->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Abilities.Add(NewAbility);
		}
	}
}

void UPlayerAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UPlayerAbilityManagerComponent::SelectAbility(TSubclassOf<APlayerAbility> Ability)
{
	if (!IsValid(Ability))
	{
		return false;
	}

	DeselectAbility(Ability);

	if (!SelectedAbility->IsA(Ability))
	{
		auto Predicate = [&](const APlayerAbility* AbilityActor)
		{
			return AbilityActor->GetClass() == Ability;
		};

		SelectedAbility = *Abilities.FindByPredicate(Predicate);
	}

	return true;
}

bool UPlayerAbilityManagerComponent::DeselectAbility(TSubclassOf<APlayerAbility> Ability)
{
	if (!IsValid(Ability))
	{
		return false;
	}

	return true;
}

bool UPlayerAbilityManagerComponent::UseSelectedAbility()
{
	if (!IsValid(SelectedAbility))
	{
		return false;
	}

	return true;
}
