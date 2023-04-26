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
	class UWidgetSwitcher* ReticleSwitcher;
	UPROPERTY(BlueprintReadOnly)
	class UImage* Reticle;
	int32 currentReticleIndex;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UWidgetSwitcher* IconSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* RiffleIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* StickyGunIcon;

	//text for current ammo and max ammo
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentAmmoText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MaxAmmoText;

	UPROPERTY()
	UMaterialInstanceDynamic* DynamicReticleMaterial[2];

public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);
	~UMyUserWidget();

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
	void SetMaterialColor(FLinearColor Color, int32 materialIndex);

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void GetLinePoints(FVector& Start, FVector& End);

	//Get Aimed Point function
	UFUNCTION(BlueprintCallable)
	void GetAimedPoint(FVector& HitLocation, FVector& EndPoint, bool& IsHitValid);

	UFUNCTION(BlueprintCallable)
	void SetAmmoText(float CurrentAmmo, float MaxAmmo);
	UFUNCTION(BlueprintCallable)
	void SetIconSwitcher(int32 WeaponIndex);


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

	FName ColorParamName = FName("Color");
};
