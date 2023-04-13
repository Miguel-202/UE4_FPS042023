// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"

//Set the tick to true and create the tick function
ABaseAI::ABaseAI() : ABaseCharacter()
{
	TimeBetweenShots = 1.0f;
	TimeSinceLastShot = 0.0f;
    Tags.Empty();
    Tags.Add("Enemy");
}

void ABaseAI::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    Shoot();
    // Do something here every tick
}

