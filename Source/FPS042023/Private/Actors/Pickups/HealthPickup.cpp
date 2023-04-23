// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/HealthPickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include <Kismet/GameplayStatics.h>

AHealthPickup::AHealthPickup()
{
	ParticleSystem->SetWorldScale3D(FVector(0.5f, 1.f, 0.35f));
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	DamageAmount = -30.f;
}

bool AHealthPickup::CanBePickedUp(ABasePlayer* Player)
{
	if (Player->IsFullHealth())
	{
		return false;
	}
	return true;
}

void AHealthPickup::HandleNoPickup(ABasePlayer* Player)
{
	//Play sound at location from sound cue
	if (NoPickupSound)
	{
		FVector Location = GetActorLocation();
		UGameplayStatics::PlaySoundAtLocation(
			this,
			NoPickupSound,
			Location,
			1.f, // VolumeMultiplier
			1.f, // PitchMultiplier
			0.f, // StartTime
			nullptr, // AttenuationSettings
			nullptr  // ConcurrencySettings
		);
	}
}

