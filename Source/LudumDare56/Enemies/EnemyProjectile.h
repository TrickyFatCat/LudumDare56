// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitDynamicSignature);

UCLASS()
class LUDUMDARE56_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()

public:
	AEnemyProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(BlueprintAssignable)
	FOnHitDynamicSignature OnHit;

public:
	UFUNCTION(BlueprintCallable)
	void SetProjectileData(const FVector& Direction, const int32 NewDamage);

private:
	FVector MovementDirection = FVector::ForwardVector;

	int32 Damage = 1;

	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent,
	                         AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         FVector NormalImpulse,
	                         const FHitResult& Hit);
};
