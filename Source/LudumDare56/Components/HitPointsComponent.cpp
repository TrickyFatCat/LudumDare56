// Fill out your copyright notice in the Description page of Project Settings.


#include "HitPointsComponent.h"


UHitPointsComponent::UHitPointsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UHitPointsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	HitPoints = MaxHitPoints;
}

bool UHitPointsComponent::IncreaseHitPoints(const int32 Amount)
{
	if (Amount <= 0 || HitPoints <= 0 || HitPoints >= MaxHitPoints)
	{
		return false;
	}

	HitPoints += Amount;
	HitPoints = FMath::Min(HitPoints, MaxHitPoints);
	OnHitPointsIncreased.Broadcast(this, HitPoints, Amount, GetNormalizedHitPoints());
	return true;
}

bool UHitPointsComponent::DecreaseHitPoints(const int32 Amount)
{
	if (Amount <= 0 || HitPoints <= 0)
	{
		return false;
	}

	HitPoints -= Amount;
	HitPoints = FMath::Max(HitPoints, 0);
	OnHitPointsDecreased.Broadcast(this, HitPoints, Amount, GetNormalizedHitPoints());

	if (HitPoints <= 0)
	{
		OnZeroHitPoints.Broadcast(this);
	}

	return true;
}

void UHitPointsComponent::SetMaxHitPoints(const int32 Value)
{
	if (Value <= 0)
	{
		return;
	}

	MaxHitPoints = Value;
	HitPoints = MaxHitPoints;
}

float UHitPointsComponent::GetNormalizedHitPoints() const
{
	if (MaxHitPoints <= 0)
	{
		return -1.f;
	}

	return static_cast<float>(HitPoints) / static_cast<float>(MaxHitPoints);
}
