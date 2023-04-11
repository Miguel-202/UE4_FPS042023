// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MyUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"


UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetHealthBarPercent(1.0);
}

void UMyUserWidget::RunOnBeginPlay()
{
	//DelegateHandler->TakeOnDamageDelegate.AddDynamic(this, &UMyUserWidget::SetHealthBarPercent);
	//TakeOnDamageDelegate.AddDynamic(this, &UMyUserWidget::SetHealthBarPercent);
	AddToViewport();
	OnUpdateHealth.AddDynamic(this, &UMyUserWidget::SetHealthBarPercent);
}

void UMyUserWidget::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UMyUserWidget::SetReticleColor(FLinearColor Color)
{
	if (Reticle)
	{
		Reticle->SetColorAndOpacity(Color);
	}
}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Get the widgets
	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	Reticle = Cast<UImage>(GetWidgetFromName(TEXT("Reticle")));
}



