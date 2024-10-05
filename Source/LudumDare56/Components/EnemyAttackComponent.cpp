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
		USkeletalMeshComponent* SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>();

		if (IsValid(SkeletalMeshComponent))
		{
			AnimInstance = SkeletalMeshComponent->GetAnimInstance();
		}
	}
}

bool UEnemyAttackComponent::StartAttack()
{
	if (!IsValid(AnimInstance) && !IsValid(AttackMontage))
	{
		return false;
	}

	AnimInstance->Montage_Play(AttackMontage);
	return true;
}

bool UEnemyAttackComponent::StopAttack()
{
	if (!IsValid(AnimInstance) || !IsValid(AttackMontage) || !AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		return false;
	}

	AnimInstance->Montage_Stop(AttackMontage->GetDefaultBlendOutTime(), AttackMontage);
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
