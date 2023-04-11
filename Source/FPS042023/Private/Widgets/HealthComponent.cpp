// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HealthComponent.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//SetHealth(MaxHealth);
	MaxHealth = 100.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	this->SetHealth(MaxHealth);
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageDel);
	//OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageDel);
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = MaxHealth;
}

void UHealthComponent::HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	
	if (CurrentHealth > 0)
	{
		//SetHealth(0);
		//DamagedActor->Destroy();
		//OnUpdateHealth.Broadcast(CurrentHealth / MaxHealth);
		CurrentHealth -= Damage;
		OnUpdateHealth.Broadcast(CurrentHealth / MaxHealth);
		//DelegateHandler->TakeOnDamageDelegate.Broadcast(CurrentHealth / MaxHealth);
	}
	else
	{
		SetHealth(0);
		GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamageDel);
		OnUpdateHealth.Broadcast(CurrentHealth / MaxHealth);
		//DelegateHandler->TakeOnDamageDelegate.Broadcast(CurrentHealth / MaxHealth);
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current Health: %f"), GetHealth()));
	
}

