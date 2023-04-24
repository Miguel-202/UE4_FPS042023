// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EffectComponent.generated.h"

UENUM(BlueprintType)
enum EDamageTypes
{
	Fire,
	NumEffects
};
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS042023_API UEffectComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Effect")
	void StartEffect(EDamageTypes Type, AActor* DamageCauser);

	//FireEffectClass
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	TSubclassOf<class AEffects_Fire> FireEffectClass;

		
};
