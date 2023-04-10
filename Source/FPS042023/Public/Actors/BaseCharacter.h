// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BaseWeaponRifle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(Abstract)
class FPS042023_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* CharacterMesh;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* CharacterSkeletalMesh;*/

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ABaseWeaponRifle> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	class ABaseWeaponRifle* Weapon;

public:	
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Shoot();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AActor> Bullet;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	ABaseWeaponRifle* GetWeapon() { return Weapon; };


};
