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
		UE_LOG(LogTemp, Error, TEXT("No Owning Pawn for Animation"));
	}
}

void UCodeRiffleAnim::PlayShootAnimation()
{
	if (FireAnimation != nullptr)
	{
		PlaySlotAnimationAsDynamicMontage(FireAnimation, "Action", 0.25f, 0.25f, 1.0f, 1);
	}
}

void UCodeRiffleAnim::PlayDeathAnimation()
{
	if (DebugDeath == false)
	{
		bool arrayIsValild = true;
		for (int i = 0; i < DeathAnimations.Num(); i++)
		{
			if (DeathAnimations[i] == nullptr)
			{
				arrayIsValild = false;
				break;
			}
		}
		if (arrayIsValild)
		{
			int random = FMath::RandRange(0, (DeathAnimations.Num() - 1));
			CurrentDeathAnimation = DeathAnimations[random];
			DebugDeath = true;
			//Wait for one second then broadcast the event
			GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, [this]()
				{
					OnCharacterDeath.Broadcast();
				}, 1.0f, false);
		}
	}
}

void UCodeRiffleAnim::PlayHurtAnimation()
{
	if (HurtAnimation != nullptr)
	{
		PlaySlotAnimationAsDynamicMontage(HurtAnimation, "Damage", 0.25f, 0.25f, 1.0f, 1);
	}
}

void UCodeRiffleAnim::SetDebugShootTrue()
{
	DebugShoot = true;
}

void UCodeRiffleAnim::PersonaUpdate()
{
	if (DebugShoot)
	{
		DebugShoot = false;
		PlayShootAnimation();
	}
}


void UCodeRiffleAnim::Shoot()
{
	if (this != nullptr)
	{
		if (CanShoot)
		{
			PlayShootAnimation();
			DebugShoot = true;
			CanShoot = false;
			// Set a timer to set CanShoot to true after 0.97 seconds
			GetWorld()->GetTimerManager().SetTimer(CanShootTimerHandle, [this]()
				{
					CanShoot = true;
				}, 0.97f, false);
		}
	}
}




