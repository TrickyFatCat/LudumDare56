﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMovementComponent.generated.h"


UCLASS(ClassGroup=(Enemy), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UEnemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyMovementComponent();

protected:
	virtual void InitializeComponent() override;
	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Activate(bool bReset) override;

	virtual void Deactivate() override;
	
public:
	UFUNCTION(BlueprintGetter)
	float GetSpeed() const { return Speed;}

	UFUNCTION(BlueprintSetter)
	void SetSpeed(const float Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetSpeed, BlueprintSetter=SetSpeed)
	float Speed = 500.f;
};


