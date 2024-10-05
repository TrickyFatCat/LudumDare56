// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyExperienceComponent.h"

#include "LudumDare56/UtilsLibrary.h"


UEnemyExperienceComponent::UEnemyExperienceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyExperienceComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UEnemyExperienceComponent::GiveExperience()
{
	return UUtilsLibrary::IncreasePlayerExperience(this, Experience);
}

void UEnemyExperienceComponent::SetExperience(const int32 Value)
{
	if (Value <= 0)
	{
		return;
	}

	Experience = Value;
}
