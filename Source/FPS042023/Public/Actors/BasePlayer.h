// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	virtual void AmmoChange(float CurrentAmmo, float MaxAmmo) override;
	
public:
	ABasePlayer();

	void BeginPlay() override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	//Create WidgetClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UMyUserWidget> WidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UMyUserWidget* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UResultsWidget> EndWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UResultsWidget* EndScreen;

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float HealthRatio);

	virtual void CharacterDeath() override;

	UFUNCTION(BlueprintCallable)
	void SwapWeaponInput();
	UFUNCTION(BlueprintCallable)
	void SetNewMaxAmmo(float newMaxAmmo);

	bool CanUpgradeClipSize();

};
