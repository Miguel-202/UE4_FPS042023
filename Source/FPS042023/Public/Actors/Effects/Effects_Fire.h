// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Effects_Fire.generated.h"

UCLASS()
class FPS042023_API AEffects_Fire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffects_Fire();

	//particle system
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	class UParticleSystemComponent* ParticleSystem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount = 5.f;

	//life span
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifeSpan")
	float LifeSpan = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifeSpan")
	float initialSize;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
