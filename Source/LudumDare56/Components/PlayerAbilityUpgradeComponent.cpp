// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAbilityUpgradeComponent.h"

#include "Kismet/GameplayStatics.h"
#include "LudumDare56/Player/Abilities/AbilityUpgrade.h"


UPlayerAbilityUpgradeComponent::UPlayerAbilityUpgradeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UPlayerAbilityUpgradeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	if (GetWorld()->IsGameWorld())
	{
		PopulateUpgradesData();
		CreateUpgradesObjects();
	}
}

void UPlayerAbilityUpgradeComponent::ChooseCurrentUpgrades()
{
	if (UpgradesData.IsEmpty())
	{
		return;
	}

	TArray<int32> NewUpgradesIndexes;

	if (UpgradesData.Num() <= UpgradesPerLevel)
	{
		for (int32 i = 0; i < UpgradesData.Num(); i++)
		{
			NewUpgradesIndexes.Add(i);
		}

		return;
	}

	int32 Index = 0;
	
	for (int32 i = 0; i < UpgradesPerLevel; i++)
	{
		do
		{
			Index = FMath::RandHelper(UpgradesData.Num() - 1);
		}
		while (PreviousUpgradesIndexes.Contains(Index) || NewUpgradesIndexes.Contains(Index));

		NewUpgradesIndexes.Add(Index);
	}
	
	PreviousUpgradesIndexes.Empty();
	PreviousUpgradesIndexes = CurrentUpgradesIndexes;
	CurrentUpgradesIndexes.Empty();
	CurrentUpgradesIndexes = NewUpgradesIndexes;
}

bool UPlayerAbilityUpgradeComponent::ActivateUpgradeByIndex(const int32 Index)
{
	if (UpgradesData.IsEmpty() || !UpgradesData.IsValidIndex(Index))
	{
		return false;
	}

	UAbilityUpgrade* AbilityUpgrade = UpgradesData[Index].UpgradeObject;
	AbilityUpgrade->ActivateUpgrade();
	OnUpgradeActivated.Broadcast(this, AbilityUpgrade);
	return true;
}

bool UPlayerAbilityUpgradeComponent::GetAbilityUpgradeDataByClass(TSubclassOf<UAbilityUpgrade> UpgradeClass,
                                                                  FAbilityUpgradeData& OutData) const
{
	if (!IsValid(UpgradeClass) || UpgradesData.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FAbilityUpgradeData& Data)
	{
		return Data.UpgradeClass == UpgradeClass;
	};

	const FAbilityUpgradeData* DataPointer = UpgradesData.FindByPredicate(Predicate);

	if (!DataPointer)
	{
		return false;
	}

	OutData = *DataPointer;
	return true;
}

bool UPlayerAbilityUpgradeComponent::GetAbilityUpgradeDataByObject(UAbilityUpgrade* UpgradeObject,
                                                                   FAbilityUpgradeData& OutData) const
{
	if (!IsValid(UpgradeObject) || UpgradesData.IsEmpty())
	{
		return false;
	}

	auto Predicate = [&](const FAbilityUpgradeData& Data)
	{
		return Data.UpgradeObject == UpgradeObject;
	};

	const FAbilityUpgradeData* DataPointer = UpgradesData.FindByPredicate(Predicate);

	if (!DataPointer)
	{
		return false;
	}

	OutData = *DataPointer;
	return true;
}

void UPlayerAbilityUpgradeComponent::PopulateUpgradesData()
{
	if (!UpgradesDataTable)
	{
		return;
	}

	UpgradesData.Empty();
	TArray<FAbilityUpgradeData*> DataArray;
	UpgradesDataTable->GetAllRows("", DataArray);

	for (const auto Data : DataArray)
	{
		UpgradesData.Add(*Data);
	}
}

void UPlayerAbilityUpgradeComponent::CreateUpgradesObjects()
{
	if (UpgradesData.IsEmpty())
	{
		return;
	}

	for (auto& Data : UpgradesData)
	{
		if (!IsValid(Data.UpgradeClass))
		{
			continue;
		}

		UObject* NewUpgradeObject = UGameplayStatics::SpawnObject(Data.UpgradeClass, GetOwner());

		if (!IsValid(NewUpgradeObject))
		{
			continue;
		}

		Data.UpgradeObject = Cast<UAbilityUpgrade>(NewUpgradeObject);
		Data.UpgradeObject->InitUpgrade(GetOwner());
	}
}
