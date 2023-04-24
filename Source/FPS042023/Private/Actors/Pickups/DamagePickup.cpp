// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/DamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/DamageType.h"


ADamagePickup::ADamagePickup() 
{
	//Super::ABasePickup();
	//Add particle system
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetWorldScale3D(FVector(0.5f, 0.5f, 0.35f));
	ParticleSystem->SetupAttachment(GetRootComponent());
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void ADamagePickup::HandlePostPickup(ABasePlayer* Player)
{
	if (DamageType)
	{
		FDamageEvent DamageEvent(DamageType);
		Player->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
		//log damage type
		UE_LOG(LogTemp, Warning, TEXT("Damage Type: %s"), *DamageType->GetName());
	}
	else
	{
		Player->TakeDamage(DamageAmount, FDamageEvent(), GetInstigatorController(), this);
	}
	ABasePickup::HandlePostPickup(Player);
}


