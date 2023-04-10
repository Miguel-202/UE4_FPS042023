// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTakeDamageDelegate, float, Damage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS042023_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	//UPROPERTY(BlueprintAssignable, Category = "Events")
	//FOnTakeDamageDelegate OnTakeDamage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//function to set health
	UFUNCTION(BlueprintCallable, Category = "Health")
		void SetHealth(float Health);
	//get helath
	UFUNCTION(BlueprintCallable, Category = "Health")
		float GetHealth() { return CurrentHealth; };

	//handle damage event
	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleDamage(float Damage);
	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(BlueprintAssignable, Category = "Game|Damage")
	FTakeAnyDamageSignature OnTakeAnyDamage;


		
};
