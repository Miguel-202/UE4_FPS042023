// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/HealthPickup.h"
#include "Particles/ParticleSystemComponent.h"

AHealthPickup::AHealthPickup()
{
	ParticleSystem->SetWorldScale3D(FVector(0.5f, 1.f, 0.35f));
	ParticleSystem->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	DamageAmount = -30.f;
}
