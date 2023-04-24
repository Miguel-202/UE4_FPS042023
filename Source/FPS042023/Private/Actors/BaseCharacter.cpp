// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseCharacter.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
    SkeletalMeshComponent->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));
    Weapon = nullptr;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
    EffectComponent = CreateDefaultSubobject<UEffectComponent>(TEXT("EffectComponent"));
    EffectComponent->SetupAttachment(SkeletalMeshComponent);
    EffectComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 140.0f));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    CodeRiffleAnimInstance = Cast<UCodeRiffleAnim>(AnimInstance);
    if (nullptr != HealthComponent && nullptr != CodeRiffleAnimInstance)
    {
        HealthComponent->OnCharacterDeath.AddDynamic(CodeRiffleAnimInstance, &UCodeRiffleAnim::PlayDeathAnimation);
        HealthComponent->OnCharacterDeath.AddDynamic(this, &ABaseCharacter::CharacterDeath);
        HealthComponent->OnCharacterHurt.AddDynamic(CodeRiffleAnimInstance, &UCodeRiffleAnim::PlayHurtAnimation);
        HealthComponent->OnCharacterHeal.AddDynamic(CodeRiffleAnimInstance, &UCodeRiffleAnim::PlayHealAnimation);

        CodeRiffleAnimInstance->OnCharacterShoot.AddDynamic(CodeRiffleAnimInstance, &UCodeRiffleAnim::SetDebugShootTrue);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HealthComponent or CodeRiffleAnimInstance is nullptr"));
    }

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

            Weapon->AmmoChangeDelegate.AddDynamic(this, &ABaseCharacter::AmmoChange);
            Weapon->StartReloadDelegate.AddDynamic(CodeRiffleAnimInstance, &UCodeRiffleAnim::PlayReloadAnimation);
        }
    }
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::CharacterDeath()
{
    //Disable collision
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::ActionEnded()
{
}

void ABaseCharacter::Shoot()
{
    if (Weapon->CanShoot() && HealthComponent->isAlive)
    {
        Weapon->Shoot();
        CodeRiffleAnimInstance->OnCharacterShoot.Broadcast();
    }
}

void ABaseCharacter::AmmoChange(float _CurrentAmmo, float _MaxAmmo)
{
}

void ABaseCharacter::Reload()
{
    if (Weapon->CanReload())
    {
        FTimerHandle ReloadTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, [this]()
            {
                Weapon->Reload();
            }, Weapon->reloadTime, false);
	}
}

bool ABaseCharacter::IsFullHealth()
{
    if (HealthComponent != nullptr)
    {
        if (HealthComponent->GetHealth() >= HealthComponent->GetMaxHealth())
        {
			return true;
		}
        else
        {
            return false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("HealthComponent is nullptr"));
        return false;
    }
}
