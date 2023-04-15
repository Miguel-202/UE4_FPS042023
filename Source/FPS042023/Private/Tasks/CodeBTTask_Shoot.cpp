// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/CodeBTTask_Shoot.h"
// #include <Actors/BaseCharacter.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "AIController.h"
#include <Interfaces/ShooterInterface.h>

EBTNodeResult::Type UCodeBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the pawn as base character
	/*ABaseCharacter* Character = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	Character->Shoot();*/
	//Log Enemy shooting 
	IShooterInterface* Shooter = Cast<IShooterInterface>(OwnerComp.GetAIOwner()->GetPawn());
	Shooter->ShootInterface();

	return EBTNodeResult::Succeeded;
}
