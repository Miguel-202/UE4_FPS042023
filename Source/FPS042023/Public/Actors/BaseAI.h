// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Interfaces/ShooterInterface.h"
#include "BaseAI.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API ABaseAI : public ABaseCharacter, public IShooterInterface
{
	GENERATED_BODY()
	
public:
	ABaseAI();
	void BeginPlay() override;

	virtual void ShootInterface() override;
	virtual void ReloadInterface() override;
	UFUNCTION()
	void AIDeath();

	//behavior tree component
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComponent;

	virtual void AmmoChange(float CurrentAmmo, float MaxAmmo) override;

	virtual void ActionEnded() override;

protected:
	FName MessageName;
};

