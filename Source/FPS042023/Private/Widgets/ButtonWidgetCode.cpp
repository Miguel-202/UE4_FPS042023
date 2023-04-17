// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ButtonWidgetCode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


void UButtonWidgetCode::NativePreConstruct()
{
    Super::NativePreConstruct();

	if (Info != nullptr)
	{
		Info->SetText(InfoText);
	}
}

UButtonWidgetCode::UButtonWidgetCode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	if (Info != nullptr)
	{
		Info->SetText(InfoText);
	}
}
