// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/MyUserWidget.h"


ABasePlayer::ABasePlayer()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;

    // Set the local position of the SpringArm to a 3th person view
    SpringArm->SetRelativeLocation(FVector(30.0f, 140.0f, 50.0f));


    // Add a third person camera to the SpringArm
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Set the local rotation of the Camera in case of needed
    Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    HealthComponent->OnUpdateHealth.AddDynamic(this, &ABasePlayer::UpdateHealthBar);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
    if (WidgetClass != nullptr)
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController != nullptr)
        {
            HUD = CreateWidget<UMyUserWidget>(PlayerController, WidgetClass);
            HUD->RunOnBeginPlay();
        }
    }
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind movement axis inputs
    PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);

    // Bind look axis inputs
    PlayerInputComponent->BindAxis("TurnHorizontal", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnVertical", this, &APawn::AddControllerPitchInput);

    // Bind jump input
    //PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);

    // Bind fire input
    PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseCharacter::Shoot);

    // Bind heal input
    //PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &ABasePlayer::Heal);

    //Bind the widget to the player
    
}

void ABasePlayer::MoveForward(float AxisValue)
{
    //if (HealthComponent->isAlive())
    {
        FRotator MakeRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
        AddMovementInput(MakeRotation.Vector(), AxisValue);
    }
}

void ABasePlayer::MoveRight(float AxisValue)
{
    FRotator MakeRotation = FRotator(0.0f, GetControlRotation().Yaw + 90.0f, 0.0f);
    AddMovementInput(MakeRotation.Vector(), AxisValue);
}

void ABasePlayer::UpdateHealthBar(float HealthRatio)
{
	HUD->SetHealthBarPercent(HealthRatio);
}

