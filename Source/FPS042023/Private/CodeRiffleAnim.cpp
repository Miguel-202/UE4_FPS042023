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

		// Get the input component from the pawn
		UInputComponent* InputComponent = Pawn->FindComponentByClass<UInputComponent>();

		// Bind the "shoot" action to the Shoot function of UCodeRiffleAnim
		if (InputComponent)
		{
			InputComponent->BindAction("shoot", IE_Pressed, this, &UCodeRiffleAnim::Shoot);
		}

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
	if (DebugShoot)
	{
		DebugShoot = false;
		PlayShootAnimation();
	}
}

void UCodeRiffleAnim::Shoot()
{
	if (CanShoot)
	{
		DebugShoot = true;
		CanShoot = false;
		// Set a timer to set CanShoot to true after 0.97 seconds
		GetWorld()->GetTimerManager().SetTimer(CanShootTimerHandle, [this]()
			{
				CanShoot = true;
			}, 0.97f, false);
	}
}




