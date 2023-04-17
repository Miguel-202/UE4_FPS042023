// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controllers/MainMenuController.h"

AMainMenuController::AMainMenuController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
	}
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
		// Create an FInputModeUIOnly object
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(MainMenuWidget->GetCachedWidget());

		// Set the input mode for the player controller
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		PlayerController->SetInputMode(InputMode);

		// Set the mouse cursor visibility
		PlayerController->bShowMouseCursor = true;


	}
}