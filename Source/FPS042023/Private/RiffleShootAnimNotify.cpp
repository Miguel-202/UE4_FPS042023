// Fill out your copyright notice in the Description page of Project Settings.

#include "RiffleShootAnimNotify.h"

#include "Actors/BaseCharacter.h"

void URiffleShootAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (character)
	{
		character->GetWeapon()->OnAnimationCompleted();
	}
}
