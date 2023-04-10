// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
	void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool DebugShoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAnimSequence* FireAnimation;

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PlayShootAnimation();

	UFUNCTION(BlueprintCallable, Category = "Animations")
	void PersonaUpdate();
	void Shoot();

	FTimerHandle CanShootTimerHandle;
	
};
