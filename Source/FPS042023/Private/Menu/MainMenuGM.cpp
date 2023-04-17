// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuGM.h"
#include "Actors/Controllers/MainMenuController.h"

AMainMenuGM::AMainMenuGM()
{
	PlayerControllerClass = AMainMenuController::StaticClass();
}