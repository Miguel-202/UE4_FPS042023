// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Interfaces/ShooterInterface.h"

//Set the tick to true and create the tick function
ABaseAI::ABaseAI() : ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    Tags.Empty();
    Tags.Add("Enemy");
}

void ABaseAI::BeginPlay()
{
    Super::BeginPlay();
}

void ABaseAI::ShootInterface()
{
    Super::Shoot(); 
}



