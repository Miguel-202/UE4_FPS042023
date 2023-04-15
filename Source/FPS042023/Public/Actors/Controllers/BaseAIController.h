// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"

#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABaseAIController();
	//Override OnPossess
	virtual void OnPossess(APawn* InPawn) override;
	//Override OnTargetPerceptionUpdated (AI Perception)
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	class UAIPerceptionComponent* MyPerceptionComponent;

protected:
	//Blackboard key for the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TAG")
	FName PlayerKey;
};
