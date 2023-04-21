// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CodeBTTask_Reload.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UCodeBTTask_Reload : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UCodeBTTask_Reload();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
protected:
	FName MessageName;
};
