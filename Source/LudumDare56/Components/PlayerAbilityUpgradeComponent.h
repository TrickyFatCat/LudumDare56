// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerAbilityUpgradeComponent.generated.h"

class UAbilityUpgrade;

USTRUCT(BlueprintType)
struct FAbilityUpgradeData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAbilityUpgrade> UpgradeClass = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	UAbilityUpgrade* UpgradeObject = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name = FText::FromString(TEXT("Ability Name"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description = FText::FromString(TEXT("Ability Description"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpgradeActivatedDynamicSignature,
                                             UPlayerAbilityUpgradeComponent*, Component,
                                             UAbilityUpgrade*, Upgrade);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UPlayerAbilityUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerAbilityUpgradeComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnUpgradeActivatedDynamicSignature OnUpgradeActivated;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* UpgradesDataTable = nullptr;

	UFUNCTION(BlueprintCallable)
	void ChooseCurrentUpgrades();

	UFUNCTION(BlueprintCallable)
	bool ActivateUpgradeByIndex(const int32 Index);

	UFUNCTION(BlueprintGetter)
	TArray<FAbilityUpgradeData> GetUpgradesData() const { return UpgradesData; }

	UFUNCTION(BlueprintGetter)
	TArray<int32> GetCurrentUpgradesIndexes() const { return CurrentUpgradesIndexes; }

	UFUNCTION(BlueprintPure)
	bool GetAbilityUpgradeDataByClass(TSubclassOf<UAbilityUpgrade> UpgradeClass, FAbilityUpgradeData& OutData) const;

	UFUNCTION(BlueprintPure)
	bool GetAbilityUpgradeDataByObject(UAbilityUpgrade* UpgradeObject, FAbilityUpgradeData& OutData) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin="2", ClampMax="5"))
	int32 UpgradesPerLevel = 3;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetUpgradesData)
	TArray<FAbilityUpgradeData> UpgradesData;

	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetCurrentUpgradesIndexes)
	TArray<int32> CurrentUpgradesIndexes = {0, 0, 0};

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<int32> PreviousUpgradesIndexes = {0, 0, 0};

private:
	UFUNCTION()
	void PopulateUpgradesData();

	UFUNCTION()
	void CreateUpgradesObjects();
};
