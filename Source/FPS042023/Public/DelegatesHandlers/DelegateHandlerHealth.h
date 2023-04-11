// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateHandlerHealth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateHealth, float, Percent);
/**
 * 
 */
UCLASS()
class FPS042023_API UDelegateHandlerHealth : public UObject
{
	GENERATED_BODY()

public:
	//Default Constructor
	UDelegateHandlerHealth();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUpdateHealth TakeOnDamageDelegate;
};
