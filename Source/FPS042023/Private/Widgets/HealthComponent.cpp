// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Delegates/Delegate.h"
//#include "Actor.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	SetHealth(MaxHealth);
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageDel);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float Health)
{
	CurrentHealth = Health;
}

void UHealthComponent::HandleDamage(float Damage)
{
	SetHealth(GetHealth() - Damage);
}

void UHealthComponent::HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	SetHealth(GetHealth() - Damage);
	if (GetHealth() <= 0)
	{
		SetHealth(0);
		//DamagedActor->Destroy();
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), GetHealth()));
}

