// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BaseWeaponRifle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeOnDamage1, float, Damage);

UCLASS(Abstract)
class FPS042023_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//Delegates
	//UPROPERTY(BlueprintAssignable, Category = "Game|Damage")
	//FTakeOnDamage1 OnTakeDamage;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AActor> Bullet;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	ABaseWeaponRifle* GetWeapon() { return Weapon; };

	//Create health component
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	class UHealthComponent* HealthComponent;

};
