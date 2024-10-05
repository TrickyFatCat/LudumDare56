// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLevelComponent.h"


UPlayerLevelComponent::UPlayerLevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerLevelComponent::InitializeComponent()
{
	Super::InitializeComponent();
	CalculateRequiredExperience();
}

bool UPlayerLevelComponent::IncreaseExperience(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	CurrentExperience += Amount;

	if (CurrentExperience >= RequiredExperience)
	{
		IncreaseLevel();
		CurrentExperience = CurrentExperience - RequiredExperience;
		CalculateRequiredExperience();
	}

	OnCurrentExperienceIncreased.Broadcast(this, CurrentExperience, GetNormalizedExperience());
	return true;
}

float UPlayerLevelComponent::GetNormalizedExperience() const
{
	if (RequiredExperience <= 0)
	{
		return -1.f;
	}

	return static_cast<float>(CurrentExperience) / static_cast<float>(RequiredExperience);
}

void UPlayerLevelComponent::IncreaseLevel()
{
	CurrentLevel += 1;
	OnLevelIncreased.Broadcast(this, CurrentLevel);
}

void UPlayerLevelComponent::CalculateRequiredExperience()
{
	if (!IsValid(ExperienceCurve))
	{
		return;
	}

	RequiredExperience = static_cast<int32>(ExperienceCurve->GetFloatValue(CurrentLevel));
}
