// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseProjectile.h"
#include "StickyBomb.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API AStickyBomb : public ABaseProjectile
{
	GENERATED_BODY()
	
public:
	AStickyBomb();
	virtual void HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void SpecialPower() override;

protected:
	float DamageRadius;
};
