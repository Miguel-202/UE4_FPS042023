// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/MainMenuWidget.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainMenuController();

	//event begin play 
	virtual void BeginPlay() override;

	//Widget class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	UMainMenuWidget* MainMenuWidget;
};
