// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyExperienceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UEnemyExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyExperienceComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UFUNCTION(BlueprintCallable)
	bool GiveExperience();
	
	UFUNCTION(BlueprintGetter)
	int32 GetExperience() const { return Experience; }

	UFUNCTION(BlueprintSetter)
	void SetExperience(const int32 Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetExperience, BlueprintSetter=SetExperience)
	int32 Experience = 10;
};
