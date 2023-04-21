// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/ButtonWidgetCode.h"
#include "END_GameInstance.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);
	~UMainMenuWidget();
	virtual void NativePreConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void PlayGame();
	UFUNCTION(BlueprintCallable, Category = "Button")
	void QuitGame();

	//QuitButton 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	class UButtonWidgetCode* QuitButton;

	//PlayButton
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button", meta = (BindWidget))
	class UButtonWidgetCode* PlayButton;

	//GameInstance
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	class UEND_GameInstance* GameInstance;

};
