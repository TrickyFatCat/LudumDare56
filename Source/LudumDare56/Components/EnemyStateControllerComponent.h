// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrickyGameModeBase.h"
#include "Components/ActorComponent.h"
#include "EnemyStateControllerComponent.generated.h"

UENUM(Blueprintable)
enum class EEnemyState : uint8
{
	Idle,
	Chase,
	Attack,
	Stun,
	Death
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyStateChangedDynamicSignature,
                                             UEnemyStateControllerComponent*, Component,
                                             EEnemyState, NewState);

UCLASS(ClassGroup=(Enemy), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UEnemyStateControllerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyStateControllerComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyStateChangedDynamicSignature OnStateChanged;
	
	UFUNCTION(BlueprintCallable)
	bool EnterIdleState();
	
	UFUNCTION(BlueprintCallable)
	bool EnterChaseState();

	UFUNCTION(BlueprintCallable)
	bool EnterAttackState();

	UFUNCTION(BlueprintCallable)
	bool EnterStunState(const float Duration);

	UFUNCTION(BlueprintCallable)
	bool EnterDeathState();

protected:
	UPROPERTY(VisibleInstanceOnly)
	EEnemyState CurrentState = EEnemyState::Stun;
	
	UFUNCTION()
	bool ChangeState(const EEnemyState NewState);

	FTimerHandle StunTimerHandle;

	UFUNCTION()
	void ExitStunState();

	UFUNCTION()
	void StopStunTimer();
};
