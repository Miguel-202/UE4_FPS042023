// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ButtonWidgetCode.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
/**
 * 
 */
UCLASS()
class FPS042023_API UButtonWidgetCode : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativePreConstruct();
	UButtonWidgetCode(const FObjectInitializer& ObjectInitializer);

	//////Button Delegate
	//UPROPERTY(BlueprintAssignable, Category = "Button")
	//FOnButtonClicked OnButtonClicked;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	class UButton* ButtonBackground;
protected:
	//Textblock 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	class UTextBlock* Info;
	//Text in textblock
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	FText InfoText;

};
