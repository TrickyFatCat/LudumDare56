// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class UEnemyDataHandler;
class UEnemyDeathComponent;
class UEnemyExperienceComponent;
enum class EEnemyState : uint8;
class UEnemyMovementComponent;
class UEnemyStateControllerComponent;
class UCapsuleComponent;
class UHitPointsComponent;

UCLASS()
class LUDUMDARE56_API AEnemyPawn : public APawn
{
	GENERATED_BODY()

public:
	AEnemyPawn();

protected:
	virtual void BeginPlay() override;

public:
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<USceneComponent> Root = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<UCapsuleComponent> CapsuleComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleInstanceOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UHitPointsComponent> HitPointsComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UEnemyStateControllerComponent> EnemyStateControllerComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UEnemyMovementComponent> EnemyMovementComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UEnemyExperienceComponent> EnemyExperienceComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UEnemyDeathComponent> EnemyDeathComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<UEnemyDataHandler> EnemyDataHandler = nullptr;

private:
	UFUNCTION()
	void HandleEnemyStateChanged(UEnemyStateControllerComponent* Component, EEnemyState NewState);

	UFUNCTION()
	void HandleAnyDamageTaken(AActor* DamagedActor,
	                          float Damage,
	                          const UDamageType* DamageType,
	                          AController* InstigatedBy,
	                          AActor* DamageCauser);


	UFUNCTION()
	void HandleZeroHitPoints(UHitPointsComponent* Component);
};
