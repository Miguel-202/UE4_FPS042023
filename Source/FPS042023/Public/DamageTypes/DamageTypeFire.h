// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "Interfaces/EffectsInterface.h"
#include "DamageTypeFire.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UDamageTypeFire : public UDamageType, public IEffectsInterface
{
	GENERATED_BODY()
	
public:
	UDamageTypeFire();
	virtual void PlayEffects(AActor* DamagedActor, AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<class UEffectComponent> FireEffectClass;
};
