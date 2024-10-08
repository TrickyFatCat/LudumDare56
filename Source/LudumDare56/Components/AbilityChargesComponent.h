﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilityChargesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnChargesChangedDynamicSignature,
                                             UAbilityChargesComponent*, Component,
                                             int32, NewCharges);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UAbilityChargesComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAbilityChargesComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnChargesChangedDynamicSignature OnChargesChanged;

	UFUNCTION(BlueprintCallable)
	bool DecreaseCharges();

	UFUNCTION(BlueprintCallable)
	bool IncreaseMaxCharges(const int32 Amount);

	UFUNCTION(BlueprintGetter)
	int32 GetCurrentCharges() const { return CurrentCharges; }
	
	UFUNCTION(BlueprintGetter)
	FTimerHandle GetRestoreTimer() const { return RestoreTimerHandle; }

	UFUNCTION(BlueprintGetter)
	float GetRestoreDuration() const { return RestoreDuration; }

	UFUNCTION(BlueprintPure)
	bool HasCharges() const { return CurrentCharges > 0; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxCharges = 2;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentCharges)
	int32 CurrentCharges = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetRestoreDuration);
	float RestoreDuration = 2.f;

	UPROPERTY(Blueprintgetter=GetRestoreTimer)
	FTimerHandle RestoreTimerHandle;

	UFUNCTION()
	void RestoreCharge();

	UFUNCTION()
	void StartRestoreTimer();

	UFUNCTION()
	void StopRestoreTimer();
};
