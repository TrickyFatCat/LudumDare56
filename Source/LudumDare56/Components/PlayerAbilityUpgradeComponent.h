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

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class LUDUMDARE56_API UPlayerAbilityUpgradeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerAbilityUpgradeComponent();

protected:
	virtual void InitializeComponent() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UDataTable* UpgradesDataTable = nullptr;

	UFUNCTION(BlueprintGetter)
	TArray<FAbilityUpgradeData> GetUpgradesData() const { return UpgradesData; }

	UFUNCTION(BlueprintPure)
	bool GetAbilityUpgradeDataByClass(TSubclassOf<UAbilityUpgrade> UpgradeClass, FAbilityUpgradeData& OutData) const;

	UFUNCTION(BlueprintPure)
	bool GetAbilityUpgradeDataByObject(UAbilityUpgrade* UpgradeObject, FAbilityUpgradeData& OutData) const;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintGetter=GetUpgradesData)
	TArray<FAbilityUpgradeData> UpgradesData;

private:
	UFUNCTION()
	void PopulateUpgradesData();

	UFUNCTION()
	void CreateUpgradesObjects();
};


