// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerTower.generated.h"

class UPlayerLevelComponent;
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
	TObjectPtr<UPlayerLevelComponent> PlayerLevelComponent = nullptr;

private:
	UFUNCTION()
	void HandleAnyDamageTaken(AActor* DamagedActor,
	                          float Damage,
	                          const UDamageType* DamageType,
	                          AController* InstigatedBy,
	                          AActor* DamageCauser);


	UFUNCTION()
	void HandleZeroHitPoints(UHitPointsComponent* Component);
};
