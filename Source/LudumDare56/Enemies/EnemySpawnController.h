﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScalableFloat.h"
#include "EnemySpawnController.generated.h"

enum class EGameModeState : uint8;
class UPlayerLevelComponent;
class UHitPointsComponent;
class AEnemyPawn;

USTRUCT(BlueprintType)
struct FEnemySpawnData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AEnemyPawn> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FScalableFloat SpawnDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FScalableFloat MaxNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentNumber = 0;

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle SpawnTimerHandle;
};

UCLASS()
class LUDUMDARE56_API AEnemySpawnController : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawnController();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float BeginPlaySpawnDelay = 3.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* EnemySpawnDataTable = nullptr;

	UFUNCTION(BlueprintCallable)
	void StopSpawn();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FEnemySpawnData> SpawnData;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVector> SpawnLocations;

	UPROPERTY()
	int32 CurrentLevel = 0;

	UFUNCTION()
	void SetSpawnData();
	
	UFUNCTION()
	void StartSpawn();

	UFUNCTION()
	void ProcessEnemySpawn(TSubclassOf<AEnemyPawn> EnemyClass);

	UFUNCTION()
	bool SpawnEnemy(TSubclassOf<AEnemyPawn> EnemyClass);

	UFUNCTION(BlueprintCallable)
	void PopulateSpawnLocations();

	UFUNCTION()
	void HandleEnemyDeath(UHitPointsComponent* Component);

	UFUNCTION()
	void HandlePlayerLevelIncreased(UPlayerLevelComponent* Component, int32 NewLevel);

	UFUNCTION()
	void HandleGameStateChanged(EGameModeState NewState);
};
