// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DelegatesHandlers/DelegateHandlerAnimations.h"
#include "CodeRiffleAnim.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot)
/**
 * 
 */
UCLASS()
class FPS042023_API UCodeRiffleAnim : public UAnimInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool CanShoot = true;
public:
	//DELEGATE
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterShoot OnCharacterShoot;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterDeath OnCharacterDeath;


	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DebugShoot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DebugDeath;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DebugReload;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimSequence*> DeathAnimations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* CurrentDeathAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* HurtAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* ReloadAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* HealAnimation;

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void SetDebugShootTrue();

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayShootAnimation();
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayDeathAnimation();
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayHurtAnimation();
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayHealAnimation();
	//play reload animation
	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayReloadAnimation();

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PersonaUpdate();
	void Shoot();

	FTimerHandle CanShootTimerHandle;
	FTimerHandle DeathTimerHandle;
	
};
