// Fill out your copyright notice in the Description page of Project Settings.


#include "END_GameInstance.h"
#include <Kismet/GameplayStatics.h>

UEND_GameInstance::UEND_GameInstance(const FObjectInitializer& ObjectInitializer)
{
	LevelNames.Add("FirstLevel");
	LevelNames.Add("MainMenu");

    NatureLevelIndex = 0;
    MainMenuLevelIndex = 1;
}

void UEND_GameInstance::Init()
{
	Super::Init();
}

void UEND_GameInstance::Shutdown()
{
	Super::Shutdown();
}

void UEND_GameInstance::LoadFirstLevel()
{
    if (NatureLevelIndex >= 0 && NatureLevelIndex < LevelNames.Num())
    {
        UGameplayStatics::OpenLevel(this, FName(LevelNames[NatureLevelIndex]), true);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid NatureLevelIndex value"));
    }
}

void UEND_GameInstance::LoadMainMenu()
{
    if (MainMenuLevelIndex >= 0 && MainMenuLevelIndex < LevelNames.Num())
    {
        UGameplayStatics::OpenLevel(this, FName(LevelNames[MainMenuLevelIndex]), true);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid MainMenuLevelIndex value"));
    }
}


void UEND_GameInstance::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}
