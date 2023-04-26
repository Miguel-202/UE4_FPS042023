// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Pickups/BasePickup.h"
#include "GameFramework/DamageType.h"
#include "DamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API ADamagePickup : public ABasePickup
{
	GENERATED_BODY()

public:
	ADamagePickup();

	virtual void HandlePostPickup(ABasePlayer* Player) override;

protected:
	//particle system
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleSystem;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float DamageAmount = 10.f;
	//damage type from damaga type class
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType>  DamageType;
};
