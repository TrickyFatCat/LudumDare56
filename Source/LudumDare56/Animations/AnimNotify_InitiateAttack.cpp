// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_InitiateAttack.h"

#include "LudumDare56/Components/EnemyAttackComponent.h"

void UAnimNotify_InitiateAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	UEnemyAttackComponent* AttackComponent = MeshComp->GetOwner()->GetComponentByClass<UEnemyAttackComponent>();

	if (AttackComponent)
	{
		AttackComponent->InitiateAttack();
	}
}
