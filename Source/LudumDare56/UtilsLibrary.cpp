// Fill out your copyright notice in the Description page of Project Settings.


#include "UtilsLibrary.h"

#include "Components/HitPointsComponent.h"

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
