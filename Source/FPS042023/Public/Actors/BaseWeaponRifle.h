// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseProjectile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponRifle.generated.h"

UCLASS()
class FPS042023_API ABaseWeaponRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeaponRifle();		

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool Animating = false;
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);
	bool CanShoot() { return !Animating; };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Shoot();
	void SetOwningPawn(APawn* NewOwningPawn);

	UFUNCTION()
	void OnAnimationCompleted();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	APawn* OwningPawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Projectile")
	TSubclassOf<ABaseProjectile> UBaseProjectile;


	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	USkeletalMeshComponent* SkeletalMesh;

	UFUNCTION()
	void Shoot();


	//UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Delegates")
	//FOnShoot OnShoot; // Delegate to handle shooting
	// Function to handle shooting


	
};
