// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStateControllerComponent.h"


UEnemyStateControllerComponent::UEnemyStateControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UEnemyStateControllerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		EnterIdleState();
	}
}

void UEnemyStateControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopStunTimer();
	
	Super::EndPlay(EndPlayReason);
}

bool UEnemyStateControllerComponent::EnterIdleState()
{
	if (CurrentState == EEnemyState::Idle)
	{
		return false;
	}

	return ChangeState(EEnemyState::Idle);
}

bool UEnemyStateControllerComponent::EnterChaseState()
{
	if (CurrentState == EEnemyState::Death)
	{
		return false;
	}

	return ChangeState(EEnemyState::Chase);
}

bool UEnemyStateControllerComponent::EnterAttackState()
{
	if (CurrentState == EEnemyState::Death)
	{
		return false;
	}

	return ChangeState(EEnemyState::Attack);
}

bool UEnemyStateControllerComponent::EnterStunState(const float Duration)
{
	if (Duration <= 0.f || CurrentState == EEnemyState::Death)
	{
		return false;
	}

	if (ChangeState(EEnemyState::Stun))
	{
		GetWorld()->GetTimerManager().SetTimer(StunTimerHandle,
		                                       this,
		                                       &UEnemyStateControllerComponent::ExitStunState,
		                                       Duration);
	}

	return false;
}

bool UEnemyStateControllerComponent::EnterDeathState()
{
	if (ChangeState(EEnemyState::Death))
	{
		StopStunTimer();
		return true;
	}

	return false;
}

bool UEnemyStateControllerComponent::ChangeState(const EEnemyState NewState)
{
	if (NewState == CurrentState)
	{
		return false;
	}

	CurrentState = NewState;
	OnStateChanged.Broadcast(this, CurrentState);
	return true;
}

void UEnemyStateControllerComponent::ExitStunState()
{
	EnterIdleState();
}

void UEnemyStateControllerComponent::StopStunTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
}
