// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Interfaces/ShooterInterface.h"

//Set the tick to true and create the tick function
ABaseAI::ABaseAI() : ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    Tags.Empty();
    Tags.Add("Enemy");
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    CodeRiffleAnimInstance = Cast<UCodeRiffleAnim>(AnimInstance);
}

void ABaseAI::BeginPlay()
{
    Super::BeginPlay();
    CodeRiffleAnimInstance->OnCharacterDeath.AddDynamic(this, &ABaseAI::AIDeath);
}

void ABaseAI::ShootInterface()
{
    Super::Shoot(); 
}

//Ai death count
void ABaseAI::AIDeath()
{
    //stop ai logic
    UBehaviorTreeComponent* BehaviorTreeComponent = FindComponentByClass<UBehaviorTreeComponent>();
    if (BehaviorTreeComponent)
    {
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	} 
    OnDestroyed.Broadcast(this);
    Destroy();
}


