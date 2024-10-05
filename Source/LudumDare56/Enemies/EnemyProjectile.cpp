// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyProjectile::AEnemyProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(SphereComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void AEnemyProjectile::BeginPlay()
{
	ProjectileMovementComponent->Velocity = MovementDirection * ProjectileMovementComponent->InitialSpeed;

	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AEnemyProjectile::HandleProjectileHit);

	Super::BeginPlay();
}

void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

auto AEnemyProjectile::SetProjectileData(const FVector& Direction, const int32 NewDamage) -> void
{
	MovementDirection = Direction;
	Damage = NewDamage <= 0 ? 1 : NewDamage;
}

void AEnemyProjectile::HandleProjectileHit(UPrimitiveComponent* HitComponent,
                                           AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp,
                                           FVector NormalImpulse,
                                           const FHitResult& Hit)
{
	if (OtherActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
	}

	OnHit.Broadcast();
	Destroy();
}
