// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseWeaponRifle.h"
#include "StickyGun.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API AStickyGun : public ABaseWeaponRifle
{
	GENERATED_BODY()

public:
	AStickyGun();

	ABaseProjectile* Shoot() override;

	virtual void HandleSpecialPower() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting")
	TArray<class ABaseProjectile*> ProjectilesShoted;
};
