// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAttackComponent.h"

#include "LudumDare56/Enemies/EnemyProjectile.h"


UEnemyAttackComponent::UEnemyAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEnemyAttackComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();
	}
}

bool UEnemyAttackComponent::StartAttack()
{
	if (!IsValid(SkeletalMeshComponent) && !IsValid(AttackMontage))
	{
		return false;
	}

	SkeletalMeshComponent->PlayAnimation(AttackMontage, true);
	return true;
}

void UEnemyAttackComponent::InitiateAttack()
{
	if (!ProjectileClass)
	{
		return;
	}

	const FVector StartPoint = GetOwner()->GetActorLocation();
	const float Theta = FMath::DegreesToRadians(AttackAngle / ProjectilesPerAttack);
	const float Phi = FMath::DegreesToRadians(AttackAngle * 0.5) - Theta * 0.5;

	for (int32 i = 0; i < ProjectilesPerAttack; i++)
	{
		FVector Direction = GetOwner()->GetActorForwardVector();
		Direction = Direction.RotateAngleAxisRad(Theta * i - Phi, FVector::UpVector);
		const FTransform SpawnTransform(FRotator::ZeroRotator, StartPoint + Direction * AttackOffset);
		AEnemyProjectile* Projectile = GetWorld()->SpawnActorDeferred<AEnemyProjectile>(ProjectileClass, SpawnTransform);

		if (Projectile)
		{
			Projectile->SetProjectileData(Direction, Damage);
			Projectile->SetOwner(GetOwner());
			Projectile->FinishSpawning(SpawnTransform);
		}
	}
	
	OnAttackInitiated.Broadcast(this);
}
