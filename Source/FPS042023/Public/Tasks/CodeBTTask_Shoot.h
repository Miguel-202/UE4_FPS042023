// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CodeBTTask_Shoot.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UCodeBTTask_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	//Event recibe execute task AI
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	FName MessageName;
};
