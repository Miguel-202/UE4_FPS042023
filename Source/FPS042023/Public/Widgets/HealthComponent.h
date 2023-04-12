// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DelegatesHandlers/DelegateHandlerHealth.h"
#include "DelegatesHandlers/DelegateHandlerAnimations.h"
#include "HealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS042023_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	//Delegates
	//UPROPERTY()
	//UDelegateHandlerHealth* DelegateHandler = NewObject<UDelegateHandlerHealth>();
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUpdateHealth OnUpdateHealth;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterDeath OnCharacterDeath;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool isAlive = true;

	//function to set health
	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float NewHealth);
	//get helath
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth() { return CurrentHealth; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	void HandleDamageDel(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
		
};
