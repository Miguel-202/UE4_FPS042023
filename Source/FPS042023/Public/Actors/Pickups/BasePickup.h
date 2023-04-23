// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Actors/BasePlayer.h>
#include "BasePickup.generated.h"

UCLASS(Abstract)
class FPS042023_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void HandleCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void HandlePostPickup(ABasePlayer* Player);
	UFUNCTION()
	virtual void HandleNoPickup(ABasePlayer* Player);
	UFUNCTION()
	virtual bool CanBePickedUp(ABasePlayer* Player);

};
