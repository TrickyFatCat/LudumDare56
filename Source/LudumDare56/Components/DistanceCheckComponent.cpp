// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceCheckComponent.h"


UDistanceCheckComponent::UDistanceCheckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 0.05f;
}

void UDistanceCheckComponent::Activate(bool bReset)
{
	SetComponentTickEnabled(true);
	Super::Activate(bReset);
}

void UDistanceCheckComponent::Deactivate()
{
	Super::Deactivate();
	SetComponentTickEnabled(false);
	bIsInRange = false;
}

void UDistanceCheckComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UDistanceCheckComponent::TickComponent(float DeltaTime,
                                            ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const bool bHasReachedTargetDistance = CheckIsInRange();

	if (!bHasReachedTargetDistance && bIsInRange)
	{
		bIsInRange = false;
		OnExitTargetRange.Broadcast(this);
	}
	else if (bHasReachedTargetDistance && !bIsInRange)
	{
		bIsInRange = true;
		OnEnterTargetRange.Broadcast(this);
	}
}

bool UDistanceCheckComponent::CheckIsInRange() const
{
	const float CurrentDistance = FVector::DistSquared(TargetLocation, GetOwner()->GetActorLocation());
	return CurrentDistance <= TargetDistance * TargetDistance;
}
