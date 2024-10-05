// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetLifeSpan.h"

void UAnimNotify_SetLifeSpan::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	MeshComp->GetOwner()->SetLifeSpan(LifeSpan);
}
