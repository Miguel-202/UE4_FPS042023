// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Widgets/HealthComponent.h"
#include "Delegates/Delegate.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CharacterMesh->SetupAttachment(GetRootComponent());
    Weapon = nullptr;

    CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
    
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (WeaponClass)
    {
        const FTransform orientationSocket = GetMesh()->GetSocketTransform("WeaponSocket", ERelativeTransformSpace::RTS_World);
        Weapon = GetWorld()->SpawnActor<ABaseWeaponRifle>(WeaponClass, orientationSocket);
        if (Weapon)
        {
            Weapon->SetOwningPawn(this);
            //Atach to socket
            FName socketName = "WeaponSocket";
            Weapon->SkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
        }
    }
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::Shoot()
{
    Weapon->Shoot();
    //Get CodeRifleAnim* from the CharacterMesh
}

