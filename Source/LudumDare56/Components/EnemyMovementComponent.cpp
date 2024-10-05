// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"


UEnemyMovementComponent::UEnemyMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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
