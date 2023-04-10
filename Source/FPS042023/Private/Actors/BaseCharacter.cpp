// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	CharacterMesh->SetupAttachment(GetRootComponent());

    CharacterMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
   // Weapon = NewObject<ABaseWeaponRifle>();
    //CharacterSkeletalMesh->SetupAttachment(GetRootComponent());

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

// Called to bind functionality to input
//void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

void ABaseCharacter::Shoot()
{
    Weapon->Shoot();
    //Get CodeRifleAnim* from the CharacterMesh
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    // Broadcast the OnTakeAnyDamage event
    OnTakeAnyDamage.Broadcast(nullptr, DamageAmount, nullptr, nullptr, nullptr);

    return ActualDamage;
}
