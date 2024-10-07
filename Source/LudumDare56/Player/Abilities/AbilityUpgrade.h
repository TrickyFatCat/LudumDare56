// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityUpgrade.generated.h"

class APlayerAbility;
/**
 * 
 */
UCLASS()
class LUDUMDARE56_API UAbilityUpgrade : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APlayerAbility> AbilityClass = nullptr;
	
	UFUNCTION()
	void ApplyUpgrade();

	UFUNCTION()
	void InitUpgrade(const AActor* PlayerActor);

protected:
	UPROPERTY(BlueprintReadOnly)
	APlayerAbility* Ability = nullptr;
	
	UFUNCTION(BlueprintNativeEvent)
	void ActivateUpgradeEffect();
};
