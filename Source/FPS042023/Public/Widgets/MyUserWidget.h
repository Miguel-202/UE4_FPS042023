// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Reticle;
public:
	UFUNCTION(BlueprintCallable)
	void SetHealthBarPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void SetReticleColor(FLinearColor Color);

	void NativeConstruct() override;
};
