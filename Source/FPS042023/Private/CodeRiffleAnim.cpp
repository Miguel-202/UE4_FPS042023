// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeRiffleAnim.h"

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
	}
}