// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/ButtonWidgetCode.h"
#include <Components/HorizontalBox.h>
#include "ResultsWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UResultsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UResultsWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativePreConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* ResultsSwitch;

	UPROPERTY(meta = (BindWidget))
	class UButtonWidgetCode* PlayAgain;
	UPROPERTY(meta = (BindWidget))
	class UButtonWidgetCode* MainMenu;
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* ButtonBox;

	//FUNCTIONS
	UFUNCTION(BlueprintCallable)
	void SetWinResults();
	UFUNCTION(BlueprintCallable)
	void SetLoseResults();

	//BUTTON FUNCTIONS
	UFUNCTION()
	void PlayAgainClicked();
	UFUNCTION()
	void MainMenuClicked();

protected:
	class UEND_GameInstance* GameInstance;

};
