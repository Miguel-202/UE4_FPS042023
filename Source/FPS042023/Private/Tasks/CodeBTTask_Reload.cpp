// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/CodeBTTask_Reload.h"
#include <Interfaces/ShooterInterface.h>
#include "AIController.h"
#include <BehaviorTree/Tasks/BTTask_BlueprintBase.h>

UCodeBTTask_Reload::UCodeBTTask_Reload(){}

EBTNodeResult::Type UCodeBTTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    MessageName = "ActionFinished";
    IShooterInterface* Shooter = Cast<IShooterInterface>(OwnerComp.GetAIOwner()->GetPawn());
    Shooter->ReloadInterface();
    OwnerComp.RegisterMessageObserver(this, MessageName);
    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::InProgress;
}

