// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "CodeBTTask_FindPoint.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UCodeBTTask_FindPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UCodeBTTask_FindPoint();

	//Radius of the sphere to search for a point
	UPROPERTY(EditAnywhere, Category = "Search")
	float SearchRadius;
	//blackboard selector output vector instance editable
	UPROPERTY(EditAnywhere, Category = "Search")
	struct FBlackboardKeySelector OutputVector;

	//event receive exectue ai equivalent from blueprint
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
};
