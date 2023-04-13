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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* DynamicReticleMaterial;

public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	//Delegate
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnUpdateHealth OnUpdateHealth;

	//Functions

	UFUNCTION(BlueprintCallable)
	void RunOnBeginPlay();

	UFUNCTION(BlueprintCallable)
	void SetHealthBarPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void SetMaterialColor(FLinearColor Color);

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void GetLinePoints(FVector& Start, FVector& End);

	//Get Aimed Point function
	UFUNCTION(BlueprintCallable)
	void GetAimedPoint(FVector& HitLocation, FVector& EndPoint, bool& IsHitValid);


private:
	//Colors
	FLinearColor DangerColor = FLinearColor(1.0f, 0.0f, 0.0f, 1.0f);
	FLinearColor WarningColor = FLinearColor(1.0f, 1.0f, 0.0f, 1.0f);
	FLinearColor SafeColor = FLinearColor(0.0f, 1.0f, 0.0f, 1.0f);
	FLinearColor Defaultcolor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//HitScan
	UPROPERTY(EditAnywhere, Category = "HitScan")
	bool IsHitScanValid = false;
	UPROPERTY(EditAnywhere, Category = "HitScan")
	FVector HitScanEnd;
	UPROPERTY(EditAnywhere, Category = "HitScan")
	FVector HitScanLocation;
};
