// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BindFunction.h"
#include "../../FPS042023.h"

// Sets default values
ABindFunction::ABindFunction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Value = 0.65f;
	TimeToCallFunction = 2.f;
	OnDefault.AddDynamic(this, &ABindFunction::BindInCode);
}

// Called when the game starts or when spawned
void ABindFunction::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Handle;
	GetWorld()->GetTimerManager().SetTimer(Handle, this, &ABindFunction::TimerCompleted, TimeToCallFunction, false);
	
}
// Called every frame
void ABindFunction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ABindFunction::BlueprintCallable()
{
	UE_LOG(LogTemp, Warning, TEXT("in C++ BlueprintCallable"))
}

void ABindFunction::BlueprintNativeEvent_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("in C++ BlueprintNativeEvent_Implementation"))
}

void ABindFunction::BlueprintImplementableEvent()
{
	UE_LOG(Game, Error, TEXT("in C++ BlueprintImplementableEvent"))
}

float ABindFunction::Pure() const
{
	return Value;
}

void ABindFunction::TimerCompleted()
{
	OnDefault.Broadcast(this);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("This is broadcasting"));
}

void ABindFunction::BindInCode(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("in C++ In Code"))
}
