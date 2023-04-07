// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeRiffleAnim.h"
#include "../../FPS042023/FPS042023.h"
#include "Animation/AnimSequence.h"


void UCodeRiffleAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (nullptr != Pawn)
	{
		FVector	Velocity = Pawn->GetVelocity();
		Speed = Velocity.Size();

		// Calculate the direction of the pawn's movement and store it in the Direction variable
		Direction = CalculateDirection(Velocity, Pawn->GetActorRotation());

		PersonaUpdate();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File does not exist!"));
	}
}

void UCodeRiffleAnim::PlayShootAnimation()
{
	if (FireAnimation != nullptr)
	{
		PlaySlotAnimation(FireAnimation, "Action", 0.25f, 0.25f, 1.0f, 1);
	}
}

void UCodeRiffleAnim::PersonaUpdate()
{
	if (FireAnimation != nullptr)
	{
		for (auto Notify : FireAnimation->Notifies)
		{
			if (Notify.NotifyName.ToString() == "ActionCompleted")
			{
				UE_LOG(Game, Warning, TEXT("Action completed Animation succesfull on CodeRiffleAnim.CPP line 59"));
			}
		}
	}

	DebugShoot = true;
	if (DebugShoot)
	{
		DebugShoot = false;
		PlayShootAnimation();
	}
}

void UCodeRiffleAnim::Shoot()
{
	DebugShoot = true;
}




