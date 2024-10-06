// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbility.h"

#include "LudumDare56/Components/AbilityChargesComponent.h"


APlayerAbility::APlayerAbility()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	AbilityChargesComponent = CreateDefaultSubobject<UAbilityChargesComponent>(TEXT("AbilityCharges"));
}

void APlayerAbility::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool APlayerAbility::UseAbility(const FVector& Location)
{
	if (!AbilityChargesComponent->HasCharges())
	{
		return false;
	}

	if (ActivateAbilityEffect(Location))
	{
		AbilityChargesComponent->DecreaseCharges();
		return true;
	}

	return false;
}

bool APlayerAbility::ActivateAbilityEffect_Implementation(const FVector& Location)
{
	return true;
}
