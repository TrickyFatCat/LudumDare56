// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitPointsRegenerationComponent.generated.h"


class UHitPointsComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UHitPointsRegenerationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHitPointsRegenerationComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DefaultRegenerationRate = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 DefaultRegenerationPower = 1;

	UFUNCTION(BlueprintCallable)
	void SetRegenerationRate(const float Value);

protected:
	UPROPERTY()
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float RegenerationRate = DefaultRegenerationRate;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 RegenerationPower = DefaultRegenerationPower;

	UPROPERTY()
	FTimerHandle RegenerationTimerHandle;

	UFUNCTION()
	void StartRegeneration();

	UFUNCTION()
	void RegenerateHitPoints();

	UFUNCTION()
	void StopRegeneration();

	UFUNCTION()
	void HandleZeroHitPoints();
};
