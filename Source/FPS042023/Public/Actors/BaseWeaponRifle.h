// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseProjectile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DelegatesHandlers/DelegateHandlerAmmo.h"
#include "BaseProjectile.h"
#include "BaseWeaponRifle.generated.h"
//include UCodeRiffleAnim
class UCodeRiffleAnim;

USTRUCT(BlueprintType)
struct FWeaponInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	int32 WeaponIconIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	TSubclassOf<UCodeRiffleAnim> WeaponAnimInstance;
};

UCLASS()
class FPS042023_API ABaseWeaponRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseWeaponRifle();		

	//delegate for reloading
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAmmoChange AmmoChangeDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStartReload StartReloadDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterActionEnded CharacterActionEndedDelegate;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	FRotator GetShootRotation();

public:	
	//Create variables for reload information
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
		float MaxAmmo;


	bool Animating = false;
	bool CanShoot();
	UFUNCTION(BlueprintCallable, Category = "Shooting")
	bool CanReload();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//void Shoot();
	void SetOwningPawn(APawn* NewOwningPawn);

	UFUNCTION()
	void OnAnimationCompleted();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	APawn* OwningPawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Shoot")
	TSubclassOf<ABaseProjectile> UBaseProjectile;


	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
	float reloadTime = 1.73;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponInfo")
	FWeaponInfo WeaponInfo;

	UFUNCTION()
	virtual ABaseProjectile* Shoot();
	UFUNCTION()
	void UpdateAmmo();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	virtual void Reload();

	UFUNCTION(BlueprintCallable, Category = "Shooting")
	virtual void UseAmmo();

	UFUNCTION(BlueprintCallable, Category = "Power")
	virtual void HandleSpecialPower();

};
