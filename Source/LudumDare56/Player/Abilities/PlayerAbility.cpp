// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbility.h"


APlayerAbility::APlayerAbility()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void APlayerAbility::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

