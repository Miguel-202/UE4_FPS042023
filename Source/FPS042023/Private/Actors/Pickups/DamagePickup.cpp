// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/DamagePickup.h"
#include "Particles/ParticleSystemComponent.h"


ADamagePickup::ADamagePickup() 
{
	//Super::ABasePickup();
	//Add particle system
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetWorldScale3D(FVector(0.5f, 0.5f, 0.35f));
	ParticleSystem->SetupAttachment(GetRootComponent());
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	//RootComponent = ParticleSystem;
}

void ADamagePickup::HandlePostPickup(ABasePlayer* Player)
{
	Player->TakeDamage(DamageAmount, FDamageEvent(), nullptr, nullptr);
	Super::HandlePostPickup(Player);
}


