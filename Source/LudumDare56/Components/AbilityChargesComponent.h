// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintGetter)
	FTimerHandle GetRestoreTimer() const { return RestoreTimerHandle; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxCharges = 2;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 CurrentCharges = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RestoreDuration = 2.f;

	UPROPERTY(Blueprintgetter=GetRestorTimerHandle)
	FTimerHandle RestoreTimerHandle;

	UFUNCTION()
	void RestoreCharge();

	UFUNCTION()
	void StartRestoreTimer();

	UFUNCTION()
	void StopRestoreTimer();
};
