// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTower.h"

#include "LudumDare56/Components/HitPointsComponent.h"


APlayerTower::APlayerTower()
{
	PrimaryActorTick.bCanEverTick = true;

	HitPointsComponent = CreateDefaultSubobject<UHitPointsComponent>(TEXT("HitPoints"));
}

void APlayerTower::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerTower::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

