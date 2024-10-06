// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityManagerComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "LudumDare56/Player/Abilities/PlayerAbility.h"


UPlayerAbilityManagerComponent::UPlayerAbilityManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	bWantsInitializeComponent = true;
}

void UPlayerAbilityManagerComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		if (AbilitiesClasses.IsEmpty())
		{
			return;
		}

		FTransform SpawnTransform = FTransform::Identity;
		Abilities.Empty();

		for (auto AbilityClass : AbilitiesClasses)
		{
			APlayerAbility* NewAbility = GetWorld()->SpawnActorDeferred<APlayerAbility>(AbilityClass, SpawnTransform);
			NewAbility->FinishSpawning(SpawnTransform);
			NewAbility->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			Abilities.Add(NewAbility);
		}
	}
}

void UPlayerAbilityManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
}


void UPlayerAbilityManagerComponent::TickComponent(float DeltaTime,
                                                   enum ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsValid(SelectedAbility) && IsValid(PlayerPawn) && IsValid(PlayerCameraManager) && IsValid(PlayerController))
	{
		FVector Location, Direction, Intersection;
		if (PlayerController->DeprojectMousePositionToWorld(Location, Direction))
		{
			const FVector LineStart = PlayerCameraManager->GetCameraLocation();
			FVector LineEnd = Location + Direction * 20000.f;
			float T = 0.f;;
			UKismetMathLibrary::LinePlaneIntersection_OriginNormal(LineStart,
			                                                       LineEnd,
			                                                       FVector::ZeroVector,
			                                                       FVector::UpVector,
			                                                       T,
			                                                       Intersection);
			Intersection.Z = 0.f;

			if (FVector::DistSquared(Intersection, PlayerPawn->GetActorLocation()) > AimRadius * AimRadius)
			{
				Intersection = Intersection.GetClampedToSize(-AimRadius, AimRadius);
			}
			
			SelectedAbility->SetActorLocation(Intersection);
		}
	}
}

bool UPlayerAbilityManagerComponent::SelectAbility(TSubclassOf<APlayerAbility> Ability)
{
	if (!IsValid(Ability))
	{
		return false;
	}

	if (IsValid(SelectedAbility))
	{
		DeselectAbility(SelectedAbility->GetClass());

		if (SelectedAbility->IsA(Ability))
		{
			SelectedAbility = nullptr;
			SetComponentTickEnabled(false);
			return false;
		}
	}

	SelectedAbility = GetAbilityByClass(Ability);
	SetComponentTickEnabled(true);
	OnAbilitySelected.Broadcast(this, SelectedAbility);
	return true;
}

bool UPlayerAbilityManagerComponent::DeselectAbility(TSubclassOf<APlayerAbility> Ability)
{
	if (!IsValid(Ability))
	{
		return false;
	}

	APlayerAbility* DeselectedAbility = GetAbilityByClass(Ability);
	OnAbilityDeselected.Broadcast(this, DeselectedAbility);
	return true;
}

bool UPlayerAbilityManagerComponent::UseSelectedAbility()
{
	if (!IsValid(SelectedAbility))
	{
		return false;
	}

	return SelectedAbility->UseAbility();
}

APlayerAbility* UPlayerAbilityManagerComponent::GetAbilityByClass(TSubclassOf<APlayerAbility> Ability)
{
	if (Abilities.IsEmpty())
	{
		return nullptr;
	}

	auto Predicate = [&](const APlayerAbility* AbilityActor)
	{
		return AbilityActor->GetClass() == Ability;
	};
	return *Abilities.FindByPredicate(Predicate);
}
