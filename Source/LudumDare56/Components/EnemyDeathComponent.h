// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyDeathComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UEnemyDeathComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyDeathComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* DeathMontage = nullptr;

	UFUNCTION(BlueprintCallable)
	bool StartDeathSequence();

protected:
	UPROPERTY()
	UAnimInstance* AnimInstance = nullptr;
};
