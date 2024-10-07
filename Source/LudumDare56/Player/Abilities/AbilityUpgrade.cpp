// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityUpgrade.h"

#include "LudumDare56/Components/PlayerAbilityManagerComponent.h"

void UAbilityUpgrade::ActivateUpgrade()
{
	ActivateUpgradeEffect();
}

void UAbilityUpgrade::InitUpgrade(const AActor* PlayerActor)
{
	if (!IsValid(PlayerActor))
	{
		return;
	}

	UPlayerAbilityManagerComponent* AbilityManagerComponent = PlayerActor->GetComponentByClass<UPlayerAbilityManagerComponent>();

	if (!IsValid(AbilityManagerComponent))
	{
		return;
	}

	Ability = AbilityManagerComponent->GetAbilityByClass(AbilityClass);
}

void UAbilityUpgrade::ActivateUpgradeEffect_Implementation()
{
}
