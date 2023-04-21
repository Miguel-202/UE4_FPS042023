// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "END_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS042023_API UEND_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UEND_GameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;
	virtual void Shutdown() override;

	//Load first level
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void LoadFirstLevel();
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void LoadMainMenu();
	UFUNCTION(BlueprintCallable, Category = "GameInstance")
	void QuitGame();

protected:
	//array of level names
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	TArray<FString> LevelNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	int32 NatureLevelIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
	int32 MainMenuLevelIndex;
};
