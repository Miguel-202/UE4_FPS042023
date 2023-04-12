// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API ABaseAI : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ABaseAI();
	void BeginPlay() override;

	//UFUNCTION(BlueprintCallable, Category = "Shooting")
		//void Shoot();

protected:
	void Tick(float DeltaTime);

private:
	float TimeSinceLastShot;
	float TimeBetweenShots;
};
