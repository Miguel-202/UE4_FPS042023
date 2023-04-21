// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/CodeBTTask_Shoot.h"
#include "AIController.h"
#include <Interfaces/ShooterInterface.h>

EBTNodeResult::Type UCodeBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	MessageName = "ActionFinished";
	IShooterInterface* Shooter = Cast<IShooterInterface>(OwnerComp.GetAIOwner()->GetPawn());
	Shooter->ShootInterface();
	OwnerComp.RegisterMessageObserver(this, MessageName);
	FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
	return EBTNodeResult::InProgress;
}

