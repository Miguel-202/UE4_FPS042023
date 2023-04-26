// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BasePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Widgets/ResultsWidget.h"
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

    //UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    //CodeRiffleAnimInstance = Cast<UCodeRiffleAnim>(AnimInstance);
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
    //CodeRiffleAnimInstance->OnCharacterDeath.AddDynamic(this, &ABasePlayer::CharacterDeath);
    if (WidgetClass != nullptr)
    {
        APlayerController* PlayerController = Cast<APlayerController>(GetController());
        if (PlayerController != nullptr)
        {
            HUD = CreateWidget<UMyUserWidget>(PlayerController, WidgetClass);
            HUD->RunOnBeginPlay();
            if (Weapon != nullptr)
                Weapon->Reload();
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

    // Bind reload input
    PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ABaseCharacter::Reload);

    // Bind heal input
    //PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &ABasePlayer::Heal);

    //Bind swap weapon input
    PlayerInputComponent->BindAction("SwapWeapon", IE_Pressed, this, &ABasePlayer::SwapWeaponInput);

    //Bind super power input
    PlayerInputComponent->BindAction("SuperPower", IE_Pressed, this, &ABasePlayer::CallSpecialPower);
    
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

void ABasePlayer::AmmoChange(float CurrentAmmo, float MaxAmmo)
{
    Super::AmmoChange(CurrentAmmo, MaxAmmo);
    HUD->SetAmmoText(CurrentAmmo, MaxAmmo);
}

void ABasePlayer::UpdateHealthBar(float HealthRatio)
{
	HUD->SetHealthBarPercent(HealthRatio);
}

void ABasePlayer::CharacterDeath()
{
	HUD->SetVisibility(ESlateVisibility::Hidden);
    DisableInput(Cast<APlayerController>(GetController()));
    Super::CharacterDeath();

    APlayerController* PlayerController = Cast<APlayerController>(GetController());
    if (PlayerController != nullptr)
    {
        EndScreen = CreateWidget<UResultsWidget>(PlayerController, EndWidgetClass);
        EndScreen->SetLoseResults();
        EndScreen->AddToViewport();
        //enable mouse
        PlayerController->bShowMouseCursor = true;
        PlayerController->bEnableClickEvents = true;
    }
}

void ABasePlayer::SwapWeaponInput()
{
    ABaseCharacter::SwapWeapon();
    HUD->SetIconSwitcher(Weapon->WeaponInfo.WeaponIconIndex);
}

void ABasePlayer::SetNewMaxAmmo(float newMaxAmmo)
{
    Weapon->MaxAmmo = Weapon->MaxAmmo + newMaxAmmo;
    AmmoChange(Weapon->CurrentAmmo, Weapon->MaxAmmo);
}

bool ABasePlayer::CanUpgradeClipSize()
{
    return true;
}
