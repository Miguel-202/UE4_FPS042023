// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "DelegateHandlerAmmo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChange, float, CurrentAmmo, float, MaxAmmo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartReload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterActionEnded);
/**
 * 
 */
UCLASS()
class FPS042023_API UDelegateHandlerAmmo : public UObject
{
	GENERATED_BODY()
	
public:
	//Default Constructor
	UDelegateHandlerAmmo();
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAmmoChange AmmoChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStartReload StartReloadDelegate;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterActionEnded CharacterActionEndedDelegate;
};
