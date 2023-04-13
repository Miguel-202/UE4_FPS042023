// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"

#include "DelegateHandlerAnimations.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterShoot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterHurt);
/**
 * 
 */
UCLASS()
class FPS042023_API UDelegateHandlerAnimations : public UObject
{
	GENERATED_BODY()
	
public:
	//Default Constructor
	UDelegateHandlerAnimations();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterDeath CharacterDeathDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterShoot CharacterShootDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterHurt CharacterHurtDelegate;
};
