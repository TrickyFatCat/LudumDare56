// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilsLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE56_API UUtilsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool ApplyHeal(AActor* TargetActor, const int32 HealPower);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject", DefaultToSelf))
	static bool IncreasePlayerExperience(UObject* WorldContextObject, const int32 Amount);
};
