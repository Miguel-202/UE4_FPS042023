// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/ClipSizePickup.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundCue.h"
#include <Components/BoxComponent.h>

AClipSizePickup::AClipSizePickup()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetWorldTransform(CollisionBox->GetRelativeTransform());
	AmmoAmount = 5;
}

void AClipSizePickup::HandlePickup(ABasePlayer* Player)
{
	Super::HandlePickup(Player);
}

void AClipSizePickup::HandlePostPickup(ABasePlayer* Player)
{
	FVector Location = GetActorLocation();
	UGameplayStatics::PlaySoundAtLocation(
		this,
		PickupSound,
		Location,
		1.f, // VolumeMultiplier
		1.f, // PitchMultiplier
		0.f, // StartTime
		nullptr, // AttenuationSettings
		nullptr  // ConcurrencySettings
	);
	Player->SetNewMaxAmmo(AmmoAmount);
	Super::HandlePostPickup(Player);
}

bool AClipSizePickup::CanBePickedUp(ABasePlayer* Player)
{
	if (!Player->CanUpgradeClipSize())
	{
		return false;
	}
	return true;
}

void AClipSizePickup::HandleNoPickup(ABasePlayer* Player)
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
