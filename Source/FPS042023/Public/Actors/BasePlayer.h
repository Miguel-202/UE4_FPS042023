// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "Widgets/HealthComponent.h"

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


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//UMyUserWidget* HUD;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<class UMyUserWidget> WidgetClass;
	
public:
	ABasePlayer();

	void BeginPlay() override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

	//Create WidgetClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UMyUserWidget> WidgetClass;

	//Create a MyUserWidget visible on blueprint category HUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UMyUserWidget* HUD;

	UFUNCTION(BlueprintCallable)
	void UpdateHealthBar(float HealthRatio);

};
