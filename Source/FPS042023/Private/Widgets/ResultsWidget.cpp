// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ResultsWidget.h"
#include "Components/WidgetSwitcher.h"
#include <END_GameInstance.h>

UResultsWidget::UResultsWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Get game instance as my END_GameInstance
	GameInstance = Cast<UEND_GameInstance>(GetGameInstance());

	//Bind functions to buttons
	if(PlayAgain != nullptr)
		PlayAgain->ButtonBackground->OnClicked.AddDynamic(this, &UResultsWidget::PlayAgainClicked);
	if (MainMenu != nullptr)
		MainMenu->ButtonBackground->OnClicked.AddDynamic(this, &UResultsWidget::MainMenuClicked);

}

UResultsWidget::~UResultsWidget()
{
	RemoveFromParent();
}

void UResultsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	//Get game instance as my END_GameInstance
	GameInstance = Cast<UEND_GameInstance>(GetGameInstance());

	//Bind functions to buttons
	if (PlayAgain != nullptr)
		PlayAgain->ButtonBackground->OnClicked.AddDynamic(this, &UResultsWidget::PlayAgainClicked);
	if (MainMenu != nullptr)
		MainMenu->ButtonBackground->OnClicked.AddDynamic(this, &UResultsWidget::MainMenuClicked);
}
void UResultsWidget::SetWinResults()
{
	ResultsSwitch->SetActiveWidgetIndex(1);
	ButtonBox->SetVisibility(ESlateVisibility::Hidden);
}

void UResultsWidget::SetLoseResults()
{
	ResultsSwitch->SetActiveWidgetIndex(0);
	ButtonBox->SetVisibility(ESlateVisibility::Visible);
}

void UResultsWidget::PlayAgainClicked()
{
	GameInstance->LoadFirstLevel();
}

void UResultsWidget::MainMenuClicked()
{
	GameInstance->LoadMainMenu();
}