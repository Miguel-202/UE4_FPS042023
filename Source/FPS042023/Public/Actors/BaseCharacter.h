// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "BaseWeaponRifle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Widgets/HealthComponent.h"
#include "Delegates/Delegate.h"
#include "CodeRiffleAnim.h"

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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Shooting")
	TSubclassOf<ABaseWeaponRifle> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	class ABaseWeaponRifle* Weapon;

	UPROPERTY()
	UCodeRiffleAnim* CodeRiffleAnimInstance;

	//character ammo changed function
	UFUNCTION()
	virtual void AmmoChange(float CurrentAmmo, float MaxAmmo);

public:	
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Shoot();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	void Reload();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	TSubclassOf<AActor> Bullet;

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	ABaseWeaponRifle* GetWeapon() { return Weapon; };

	//Create health component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	class UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void CharacterDeath();

	UFUNCTION(BlueprintCallable, Category = "Events")
	virtual void ActionEnded();
};
