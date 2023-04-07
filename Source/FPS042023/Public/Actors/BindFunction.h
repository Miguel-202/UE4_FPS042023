// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BindFunction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher, AActor*, ParamName);

UCLASS()
class FPS042023_API ABindFunction : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABindFunction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Function")
	void BlueprintCallable();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Function")
	void BlueprintNativeEvent();
	virtual void BlueprintNativeEvent_Implementation();


	UFUNCTION(BlueprintCallable, Category = "Function")
	void BlueprintImplementableEvent();

	//Pure
	float Value;
	UFUNCTION(BlueprintCallable, Category = "Function|Pure")
	float Pure() const;

	//Event Dispatcher
	UPROPERTY(BlueprintCallable, Category = "Function")
	FEventDispatcher OnAction;

	UPROPERTY(BlueprintAssignable, Category = "Function")
	FEventDispatcher OnAssignable;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Function")
	FEventDispatcher OnDefault;


	//Bind and timer
	float TimeToCallFunction;
	//will crash without a UFUNCTION
	UFUNCTION()
	void TimerCompleted();

	UFUNCTION()
	void BindInCode(AActor* Actor);

};
