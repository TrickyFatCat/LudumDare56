// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"


UEnemyMovementComponent::UEnemyMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bAutoActivate = false;
	bWantsInitializeComponent = true;
}

void UEnemyMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UEnemyMovementComponent::TickComponent(float DeltaTime,
                                            ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->AddActorWorldOffset(GetOwner()->GetActorForwardVector() * Speed * DeltaTime);
}

void UEnemyMovementComponent::Activate(bool bReset)
{
	Super::Activate(bReset);

	SetComponentTickEnabled(true);
}

void UEnemyMovementComponent::Deactivate()
{
	Super::Deactivate();

	SetComponentTickEnabled(false);
}

void UEnemyMovementComponent::SetSpeed(const float Value)
{
	if (Value < 0.f)
	{
		return;
	}

	Speed = Value;
}
