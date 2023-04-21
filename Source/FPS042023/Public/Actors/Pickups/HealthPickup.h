// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/DamagePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API AHealthPickup : public ADamagePickup
{
	GENERATED_BODY()
	
public:
	AHealthPickup();
	//virtual void HandlePostPickup(ABasePlayer* Player) override;
};
