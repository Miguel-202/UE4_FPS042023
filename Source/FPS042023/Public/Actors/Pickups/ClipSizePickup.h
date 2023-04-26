// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/BasePickup.h"
#include "ClipSizePickup.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API AClipSizePickup : public ABasePickup
{
	GENERATED_BODY()

public:
	AClipSizePickup();

	virtual void HandlePickup(ABasePlayer* Player) override;
	virtual bool CanBePickedUp(ABasePlayer* Player) override;
	virtual void HandleNoPickup(ABasePlayer* Player) override;
	virtual void HandlePostPickup(ABasePlayer* Player) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
	class UStaticMeshComponent* Mesh;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties")
	int32 AmmoAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties | Souns")
	class USoundCue* PickupSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup Properties | Sound")
	class USoundCue* NoPickupSound;
};
