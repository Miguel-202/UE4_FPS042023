// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HealthComponent.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	//SetHealth(MaxHealth);
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamageDel);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetHealth(float NewHealth)
{
	CurrentHealth = NewHealth;
}

void UHealthComponent::HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	
	if (isAlive)
	{
		if (CurrentHealth > 0)
		{
			CurrentHealth -= Damage;
			OnUpdateHealth.Broadcast(CurrentHealth / MaxHealth);

			//If the player health gets to 0 during this shoot, it won't need to wait until the next shoot to die, it will die immediately
			if (CurrentHealth <= 0)
			{
				CurrentHealth = 0;
				GetOwner()->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamageDel);
				OnUpdateHealth.Broadcast(CurrentHealth / MaxHealth);
				OnCharacterDeath.Broadcast();
				isAlive = false;
			}
			else
			{
				if (Damage > 0)
					OnCharacterHurt.Broadcast();
				else
				{
					OnCharacterHeal.Broadcast();
				}
			}
		}
	}
	
}

