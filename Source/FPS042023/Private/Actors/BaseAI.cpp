// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"

//Set the tick to true and create the tick function
ABaseAI::ABaseAI() : ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseAI::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Shoot();
    //wait 3 seconds
    TimeSinceLastShot += DeltaTime;
    if (TimeSinceLastShot >= TimeBetweenShots)
    {
		TimeSinceLastShot = 0.0f;
        Weapon->Animating = false;
	}
    // Do something here every tick
}

