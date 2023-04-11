// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DelegatesHandlers/DelegateHandlerHealth.h"
#include "MyUserWidget.generated.h"

UCLASS()
class FPS042023_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Reticle;
public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	//Delegate
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUpdateHealth OnUpdateHealth;
	//UPROPERTY()
	//UDelegateHandlerHealth* DelegateHandler = NewObject<UDelegateHandlerHealth>();

	UFUNCTION(BlueprintCallable)
	void RunOnBeginPlay();

	UFUNCTION(BlueprintCallable)
	void SetHealthBarPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void SetReticleColor(FLinearColor Color);

	void NativeConstruct() override;
};
