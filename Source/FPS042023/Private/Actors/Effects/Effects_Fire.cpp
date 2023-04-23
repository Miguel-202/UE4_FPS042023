// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Effects/Effects_Fire.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AEffects_Fire::AEffects_Fire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//set particle system component as root component
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
	RootComponent = ParticleSystem;
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AEffects_Fire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffects_Fire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//apply damage to atached actor
	if (GetAttachParentActor())
	{
		UGameplayStatics::ApplyDamage(GetAttachParentActor(), DeltaTime * DamageAmount, GetInstigatorController(), GetInstigator(), nullptr);
	}
}

