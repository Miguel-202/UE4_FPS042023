// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ABasePlayer::ABasePlayer()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->bUsePawnControlRotation = true;

    // Set the local position of the SpringArm to (0, 0, 60)
    SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));


    // Add a third person camera to the SpringArm
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Set the local rotation of the Camera to (0, -20, 0)
    Camera->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));
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
    //PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABasePlayer::Fire);

    // Bind heal input
    //PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &ABasePlayer::Heal);

}

void ABasePlayer::MoveForward(float AxisValue)
{
    FRotator MakeRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);
    AddMovementInput(MakeRotation.Vector(), AxisValue);
}

void ABasePlayer::MoveRight(float AxisValue)
{
    FRotator MakeRotation = FRotator(0.0f, GetControlRotation().Yaw + 90.0f, 0.0f);
    AddMovementInput(MakeRotation.Vector(), AxisValue);
}
