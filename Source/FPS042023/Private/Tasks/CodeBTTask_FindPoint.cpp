// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/CodeBTTask_FindPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"

UCodeBTTask_FindPoint::UCodeBTTask_FindPoint()
{
	//set the node name
	NodeName = TEXT("Find Point Code");
	SearchRadius = 1000.0f;
}

EBTNodeResult::Type UCodeBTTask_FindPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get Random Location in Navigable Radius getting the navmesh system taking the actor location as origin and the search radius as radius
	FVector RandomLocation = UNavigationSystemV1::GetRandomPointInNavigableRadius(GetWorld(), OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), SearchRadius);
	//FVector RandomLocation = { 1,1,1 };
	//If the random location is valid
	if (RandomLocation == FVector::ZeroVector)
	{
		//return failed
		UE_LOG(LogTemp, Warning, TEXT("Failed to find point"));
		return EBTNodeResult::Failed;
	}
	// Get a reference to the Blackboard component
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Set the Destination key on the Blackboard to the RandomLocation vector
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsVector("Destination", RandomLocation);
	}


	return EBTNodeResult::Succeeded;
}
