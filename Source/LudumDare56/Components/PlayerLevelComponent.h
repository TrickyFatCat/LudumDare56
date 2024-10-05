// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerLevelComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelIncreasedDyanmicSignature,
                                             UPlayerLevelComponent*, Component,
                                             const int32, NewLevel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCurrentExperienceIncreasedDynamicSignature,
                                               UPlayerLevelComponent*, Component,
                                               const int32, CurrentExperience,
                                               const float, NormalizedExperience);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UPlayerLevelComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerLevelComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnLevelIncreasedDyanmicSignature OnLevelIncreased;
	
	UPROPERTY(BlueprintAssignable)
	FOnCurrentExperienceIncreasedDynamicSignature OnCurrentExperienceIncreased;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* ExperienceCurve = nullptr;
	
	UFUNCTION(BlueprintCallable)
	bool IncreaseExperience(const int32 Amount);

	UFUNCTION(BlueprintGetter)
	int32 GetCurrentLevel() const { return CurrentLevel; }

	UFUNCTION(BlueprintGetter)
	int32 GetCurrentExperience() const { return CurrentExperience; }

	UFUNCTION(BlueprintGetter)
	int32 GetRequiredExperience() const { return RequiredExperience; }

	UFUNCTION(BlueprintPure)
	float GetNormalizedExperience() const;
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentLevel)
	int32 CurrentLevel = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentExperience)
	int32 CurrentExperience = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetRequiredExperience)
	int32 RequiredExperience = 100;

	UFUNCTION()
	void IncreaseLevel();

	UFUNCTION()
	void CalculateRequiredExperience();
};
