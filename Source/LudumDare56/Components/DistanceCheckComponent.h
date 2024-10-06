// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DistanceCheckComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnterTargetRangeDyanmicSignature,
                                            UDistanceCheckComponent*, Component);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExitTargetRangeDyanmicSignature,
                                            UDistanceCheckComponent*, Component);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UDistanceCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDistanceCheckComponent();

protected:
	virtual void Activate(bool bReset) override;

	virtual void Deactivate() override;

	virtual void InitializeComponent() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnterTargetRangeDyanmicSignature OnEnterTargetRange;

	UPROPERTY(BlueprintAssignable)
	FOnExitTargetRangeDyanmicSignature OnExitTargetRange;

	UPROPERTY(VisibleInstanceOnly)
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly)
	float TargetDistance = 200.f;

	UFUNCTION(BlueprintPure)
	bool CheckIsInRange() const;

protected:
	UPROPERTY(VisibleInstanceOnly)
	bool bIsInRange = false;
};
