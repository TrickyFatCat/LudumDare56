// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityChargesComponent.h"


UAbilityChargesComponent::UAbilityChargesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UAbilityChargesComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

bool UAbilityChargesComponent::DecreaseCharges()
{
	if (CurrentCharges <= 0)
	{
		return false;
	}

	CurrentCharges -= 1;
	StartRestoreTimer();
	OnChargesChanged.Broadcast(this, CurrentCharges);
	return true;
}

bool UAbilityChargesComponent::IncreaseMaxCharges(const int32 Amount)
{
	if (Amount <= 0)
	{
		return false;
	}

	MaxCharges += Amount;
	StartRestoreTimer();
	return true;
}

void UAbilityChargesComponent::RestoreCharge()
{
	if (CurrentCharges >= MaxCharges)
	{
		return;
	}

	CurrentCharges += 1;
	CurrentCharges = FMath::Min(CurrentCharges, MaxCharges);

	if (CurrentCharges >= MaxCharges)
	{
		StopRestoreTimer();
	}

	OnChargesChanged.Broadcast(this, CurrentCharges);
}

void UAbilityChargesComponent::StartRestoreTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (TimerManager.IsTimerActive(RestoreTimerHandle))
	{
		return;
	}

	TimerManager.SetTimer(RestoreTimerHandle, this, &UAbilityChargesComponent::RestoreCharge, RestoreDuration, true);
}

void UAbilityChargesComponent::StopRestoreTimer()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	if (!TimerManager.IsTimerActive(RestoreTimerHandle))
	{
		return;
	}

	TimerManager.ClearTimer(RestoreTimerHandle);
}
