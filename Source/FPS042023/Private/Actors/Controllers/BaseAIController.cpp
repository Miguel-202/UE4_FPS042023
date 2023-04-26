// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/BaseAIController.h"
#include "Actors/BaseAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include <Perception/AISenseConfig_Sight.h>
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/BasePlayer.h"

ABaseAIController::ABaseAIController() : AAIController()
{
	MyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ABaseAIController::OnPossess(APawn* InPawn)
{
	// Call the parent class
	Super::OnPossess(InPawn);
	// Get a reference to the AI character
	ABaseAI* AICharacter = Cast<ABaseAI>(InPawn);

	AAIController::RunBehaviorTree(AICharacter->BehaviorTree);

    MyPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABaseAIController::OnTargetPerceptionUpdated);
	
}

void ABaseAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    //cast Actor as Player
    ABasePlayer* Player = Cast<ABasePlayer>(Actor);
    if (nullptr != Player)
    {
        // Check if the stimulus is successful
        if (Stimulus.WasSuccessfullySensed())
        {
            GetBlackboardComponent()->SetValueAsObject(PlayerKey, Player);
        }
        else
        {
            GetBlackboardComponent()->ClearValue(PlayerKey);
        }
    }
}
