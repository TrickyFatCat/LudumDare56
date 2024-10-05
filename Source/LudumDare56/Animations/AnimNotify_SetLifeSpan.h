// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetLifeSpan.generated.h"

/**
 * 
 */
UCLASS()
class LUDUMDARE56_API UAnimNotify_SetLifeSpan : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp,
	                    UAnimSequenceBase* Animation,
	                    const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditAnywhere)
	float LifeSpan = 1.0f;
};
