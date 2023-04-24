// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/EffectComponent.h"
#include <Actors/Effects/Effects_Fire.h>

// Sets default values for this component's properties
UEffectComponent::UEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEffectComponent::StartEffect(EDamageTypes Type, AActor* DamageCauser)
{
	AEffects_Fire* FireEffect;
	FActorSpawnParameters SpawnParams;
	switch (Type)
	{
	case EDamageTypes::Fire:
		////spawn fire effect
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = DamageCauser;
		FireEffect = GetWorld()->SpawnActor<AEffects_Fire>(FireEffectClass, DamageCauser->GetTransform(), SpawnParams);
		////attach fire effect to damaged actor
		FireEffect->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
		break;
	default:
		break;
	}
}

