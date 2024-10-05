// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAttackComponent.generated.h"

class AEnemyProjectile;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttackInitiatedDynamicSignature,
                                            UEnemyAttackComponent*, Component);

UCLASS(ClassGroup=(Enemy), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UEnemyAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UEnemyAttackComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAttackInitiatedDynamicSignature OnAttackInitiated;
	
	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* AttackMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Range = 200.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Damage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AEnemyProjectile> ProjectileClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ProjectilesPerAttack = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackAngle = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector AttackOffset = FVector::Zero();

	UFUNCTION(BlueprintCallable)
	bool StartAttack();

	UFUNCTION(BlueprintCallable)
	void InitiateAttack();

protected:
	UPROPERTY()
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
};
