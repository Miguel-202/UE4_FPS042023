// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MainMenuWidget.h"
#include "END_GameInstance.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    if (GameInstance == nullptr)
        GameInstance = Cast<UEND_GameInstance>(GetGameInstance());
    // Bind the OnButtonClicked event of the PlayButton instance to the PlayGame function
    if (PlayButton != nullptr)
    {
        PlayButton->ButtonBackground->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
    }

    // Bind the OnButtonClicked event of the QuitButton instance to the QuitGame function
    if (QuitButton != nullptr)
    {
        QuitButton->ButtonBackground->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
    }
}

void UMainMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

    if (GameInstance == nullptr)
        GameInstance = Cast<UEND_GameInstance>(GetGameInstance());

	// Bind the OnButtonClicked event of the PlayButton instance to the PlayGame function
    if (PlayButton != nullptr)
    {
        PlayButton->ButtonBackground->OnClicked.AddDynamic(this, &UMainMenuWidget::PlayGame);
    }

    // Bind the OnButtonClicked event of the QuitButton instance to the QuitGame function
    if (QuitButton != nullptr)
    {
        QuitButton->ButtonBackground->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitGame);
    }


}

void UMainMenuWidget::PlayGame()
{
    UE_LOG(LogTemp, Warning, TEXT("PlayGame() called"));
    if (GameInstance != nullptr)
    {
		GameInstance->LoadFirstLevel();
	}
}

void UMainMenuWidget::QuitGame()
{
    UE_LOG(LogTemp, Warning, TEXT("QuitGame() called"));
    if (GameInstance != nullptr)
    {
        GameInstance->QuitGame();
    }
}

