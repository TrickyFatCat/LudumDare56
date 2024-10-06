// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilityManagerComponent.generated.h"


class APlayerAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilitySelectedDynamicSignature,
                                             UPlayerAbilityManagerComponent*, Component,
                                             APlayerAbility*, Ability);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityDeselectedDynamicSignature,
                                             UPlayerAbilityManagerComponent*, Component,
                                             APlayerAbility*, Ability);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UPlayerAbilityManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerAbilityManagerComponent();

protected:
	virtual void InitializeComponent() override;

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAbilitySelectedDynamicSignature OnAbilitySelected;

	UPROPERTY(BlueprintAssignable)
	FOnAbilityDeselectedDynamicSignature OnAbilityDeselected;
	
	UFUNCTION(BlueprintCallable)
	bool SelectAbility(TSubclassOf<APlayerAbility> Ability);

	UFUNCTION(BlueprintCallable)
	bool DeselectAbility(TSubclassOf<APlayerAbility> Ability);

	UFUNCTION(BlueprintCallable)
	bool UseSelectedAbility();

	UFUNCTION(BlueprintPure)
	APlayerAbility* GetAbilityByClass(TSubclassOf<APlayerAbility> Ability);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<APlayerAbility>> AbilitiesClasses;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<APlayerAbility*> Abilities;

	UPROPERTY(VisibleInstanceOnly)
	APlayerAbility* SelectedAbility = nullptr;
};
