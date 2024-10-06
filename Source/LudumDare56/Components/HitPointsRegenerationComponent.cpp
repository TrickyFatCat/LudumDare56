// Fill out your copyright notice in the Description page of Project Settings.


#include "HitPointsRegenerationComponent.h"

#include "HitPointsComponent.h"


UHitPointsRegenerationComponent::UHitPointsRegenerationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UHitPointsRegenerationComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		HitPointsComponent = GetOwner()->GetComponentByClass<UHitPointsComponent>();
		StartRegeneration();
	}
}

void UHitPointsRegenerationComponent::StartRegeneration()
{
	if (!IsActive())
	{
		return;
	}

	const float RegenerationDelay = RegenerationRate <= 0.f ? 1.f : 1.f / RegenerationRate;
	GetWorld()->GetTimerManager().SetTimer(RegenerationTimerHandle,
	                                       this,
	                                       &UHitPointsRegenerationComponent::RegenerateHitPoints,
	                                       RegenerationDelay,
	                                       true);
}

void UHitPointsRegenerationComponent::RegenerateHitPoints()
{
	if (!IsValid(HitPointsComponent))
	{
		return;
	}

	HitPointsComponent->IncreaseHitPoints(RegenerationPower);
}

void UHitPointsRegenerationComponent::StopRegeneration()
{
	GetWorld()->GetTimerManager().ClearTimer(RegenerationTimerHandle);
	Deactivate();
}

void UHitPointsRegenerationComponent::HandleZeroHitPoints()
{
	StopRegeneration();
}
