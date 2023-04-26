// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseAI.h"
#include "Interfaces/ShooterInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <AIController.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>

//Set the tick to true and create the tick function
ABaseAI::ABaseAI() : ABaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    Tags.Empty();
    Tags.Add("Enemy");
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    CurrentAnimInstance = Cast<UCodeRiffleAnim>(AnimInstance);
}

void ABaseAI::BeginPlay()
{
    Super::BeginPlay();
    CurrentAnimInstance->OnCharacterDeath.AddDynamic(this, &ABaseAI::AIDeath);
    BehaviorTreeComponent = NewObject<UBehaviorTreeComponent>(GetOwner());
    BehaviorTreeComponent->RegisterComponent();
    Weapon->Reload();
    Weapon->CharacterActionEndedDelegate.AddDynamic(this, &ABaseAI::ActionEnded);
    MessageName = "ActionFinished";
}

void ABaseAI::ShootInterface()
{
    Super::Shoot(); 
}

void ABaseAI::ReloadInterface()
{
	Super::Reload();
}

//Ai death count
void ABaseAI::AIDeath()
{
    if (BehaviorTreeComponent)
    {
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	} 
    OnDestroyed.Broadcast(this);
    Destroy();
}

void ABaseAI::AmmoChange(float CurrentAmmo, float MaxAmmo)
{
    Super::AmmoChange(CurrentAmmo, MaxAmmo);
    //update the float ammo count on my blackboard of my ai controller
    if (BehaviorTreeComponent)
    {
        UBlackboardComponent* BlackboardComponent = BehaviorTreeComponent->GetBlackboardComponent();
        if (BlackboardComponent)
        {
            BlackboardComponent->SetValueAsFloat("Ammo", CurrentAmmo);
        }
	}
}

void ABaseAI::ActionEnded()
{
    UAIBlueprintHelperLibrary::SendAIMessage(this, MessageName, this, true);
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Action Ended");

}


