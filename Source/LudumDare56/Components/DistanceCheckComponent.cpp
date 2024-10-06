﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceCheckComponent.h"


UDistanceCheckComponent::UDistanceCheckComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 0.05f;
}

void UDistanceCheckComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	SetComponentTickEnabled(true);
}

void UDistanceCheckComponent::Deactivate()
{
	Super::Deactivate();
	SetComponentTickEnabled(false);
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
	
	if (bHasReachedTargetDistance > TargetDistance && bIsInRange)
	{
		bIsInRange = false;
		OnExitTargetRange.Broadcast(this);
	}
	else if (bHasReachedTargetDistance <= TargetDistance && !bIsInRange)
	{
		bIsInRange = true;
		OnEnterTargetRange.Broadcast(this);
	}
}

bool UDistanceCheckComponent::CheckIsInRange() const
{
	const float CurrentDistance = FVector::DistSquared(TargetLocation, GetOwner()->GetActorLocation());
	return CurrentDistance <= TargetDistance;
}
