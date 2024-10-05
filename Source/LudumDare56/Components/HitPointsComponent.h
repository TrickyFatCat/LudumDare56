// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitPointsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHitPointsIncreasedDynamicSignature,
                                              UHitPointsComponent*, Component,
                                              int32, NewHitPoints,
                                              int32, DeltaHitPoints,
                                              float, NormalizedHitPoints);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHitPointsDecreasedDynamicSignature,
                                              UHitPointsComponent*, Component,
                                              int32, NewHitPoints,
                                              int32, DeltaHitPoints,
                                              float, NormalizedHitPoints);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZeroHitPointsDynamicSignature,
                                            UHitPointsComponent*, Component);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UHitPointsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitPointsComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnHitPointsIncreasedDynamicSignature OnHitPointsIncreased;
	
	UPROPERTY(BlueprintAssignable)
	FOnHitPointsDecreasedDynamicSignature OnHitPointsDecreased;

	UPROPERTY(BlueprintAssignable)
	FOnZeroHitPointsDynamicSignature OnZeroHitPoints;
	
	UFUNCTION(BlueprintCallable)
	bool IncreaseHitPoints(const int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool DecreaseHitPoints(const int32 Amount);

	UFUNCTION(BlueprintGetter)
	int32 GetHitPoints() const { return HitPoints; }

	UFUNCTION(BlueprintGetter)
	int32 GetMaxHitPoints() const { return MaxHitPoints; }

	UFUNCTION(BlueprintSetter)
	void SetMaxHitPoints(const int32 Value);

	UFUNCTION(BlueprintPure)
	float GetNormalizedHitPoints() const;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetHitPoints)
	int32 HitPoints = 1;

	UPROPERTY(EditDefaultsOnly,
		BlueprintGetter=GetMaxHitPoints,
		BlueprintSetter=SetMaxHitPoints,
		meta=(AllowPrivateAccess=true))
	int32 MaxHitPoints = 1;
};
