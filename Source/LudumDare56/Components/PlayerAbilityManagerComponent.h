// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilityManagerComponent.generated.h"


class APlayerAbility;

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
	UFUNCTION(BlueprintCallable)
	bool SelectAbility(TSubclassOf<APlayerAbility> Ability);

	UFUNCTION(BlueprintCallable)
	bool DeselectAbility(TSubclassOf<APlayerAbility> Ability);

	UFUNCTION(BlueprintCallable)
	bool UseSelectedAbility();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<APlayerAbility>> AbilitiesClasses;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<APlayerAbility*> Abilities;

	UPROPERTY(VisibleInstanceOnly)
	APlayerAbility* SelectedAbility = nullptr;
};
