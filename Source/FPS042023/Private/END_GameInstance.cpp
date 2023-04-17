// Fill out your copyright notice in the Description page of Project Settings.


#include "END_GameInstance.h"
#include <Kismet/GameplayStatics.h>

UEND_GameInstance::UEND_GameInstance(const FObjectInitializer& ObjectInitializer)
{
	LevelNames.Add("FirstLevel");
	LevelNames.Add("MainMenu");
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
	UGameplayStatics::OpenLevel(this, FName(LevelNames[NatureLevelIndex]), true);
}

void UEND_GameInstance::LoadMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName(LevelNames[MainMenuLevelIndex]), true);
}

void UEND_GameInstance::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController != nullptr)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}
