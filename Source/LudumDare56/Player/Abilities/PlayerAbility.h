// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerAbility.generated.h"

class UAbilityChargesComponent;

UCLASS()
class LUDUMDARE56_API APlayerAbility : public AActor
{
	GENERATED_BODY()

public:
	APlayerAbility();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool UseAbility();

	UFUNCTION(BlueprintGetter)
	UAbilityChargesComponent* GetAbilityChargesComponent() const { return AbilityChargesComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetAbilityChargesComponent)
	TObjectPtr<UAbilityChargesComponent> AbilityChargesComponent = nullptr;

	UFUNCTION(BlueprintNativeEvent)
	bool ActivateAbilityEffect();

	
};
