// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTower.generated.h"

class UHitPointsComponent;

UCLASS()
class LUDUMDARE56_API APlayerTower : public APawn
{
	GENERATED_BODY()

public:
	APlayerTower();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;
};
