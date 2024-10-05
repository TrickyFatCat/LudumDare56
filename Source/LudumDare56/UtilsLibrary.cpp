// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsLibrary.h"

#include "Components/HitPointsComponent.h"
#include "Components/PlayerLevelComponent.h"
#include "Kismet/GameplayStatics.h"

bool UUtilsLibrary::ApplyHeal(AActor* TargetActor, const int32 HealPower)
{
	if (!IsValid(TargetActor))
	{
		return false;
	}

	UHitPointsComponent* HitPointsComponent = TargetActor->GetComponentByClass<UHitPointsComponent>();

	if (!IsValid(HitPointsComponent))
	{
		return false;
	}

	return HitPointsComponent->IncreaseHitPoints(HealPower);
}

bool UUtilsLibrary::IncreasePlayerExperience(UObject* WorldContextObject, const int32 Amount)
{
	if (!IsValid(WorldContextObject))
	{
		return false;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);

	if (!IsValid(PlayerPawn))
	{
		return false;
	}

	UPlayerLevelComponent* PlayerLevelComponent = PlayerPawn->GetComponentByClass<UPlayerLevelComponent>();

	if (!IsValid(PlayerLevelComponent))
	{
		return false;
	}

	return PlayerLevelComponent->IncreaseExperience(Amount);
}