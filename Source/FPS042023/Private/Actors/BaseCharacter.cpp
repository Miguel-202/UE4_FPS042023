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
    SetReferences();
    BindEvents();
    BindWeaponAndAnimationEvents();
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
        CurrentAnimInstance->OnCharacterShoot.Broadcast();
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

void ABaseCharacter::BindEvents()
{
    if (nullptr != HealthComponent)
    {
        HealthComponent->OnCharacterDeath.AddDynamic(this, &ABaseCharacter::CharacterDeath);
    }
    else
    {
		UE_LOG(LogTemp, Error, TEXT("HealthComponent is nullptr"));
	}

}

void ABaseCharacter::BindWeaponAndAnimationEvents()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    CurrentAnimInstance = Cast<UCodeRiffleAnim>(AnimInstance);
    if (nullptr != Weapon)
    {
        Weapon->AmmoChangeDelegate.AddDynamic(this, &ABaseCharacter::AmmoChange);
        Weapon->StartReloadDelegate.AddDynamic(CurrentAnimInstance, &UCodeRiffleAnim::PlayReloadAnimation);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Weapon is nullptr"));
    }
    if (nullptr != CurrentAnimInstance)
    {
        CurrentAnimInstance->OnCharacterShoot.AddDynamic(CurrentAnimInstance, &UCodeRiffleAnim::SetDebugShootTrue);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("CodeRiffleAnimInstance is nullptr"));
    }
    if (nullptr != HealthComponent)
    {
        HealthComponent->OnCharacterDeath.AddDynamic(CurrentAnimInstance, &UCodeRiffleAnim::PlayDeathAnimation);
        HealthComponent->OnCharacterHurt.AddDynamic(CurrentAnimInstance, &UCodeRiffleAnim::PlayHurtAnimation);
        HealthComponent->OnCharacterHeal.AddDynamic(CurrentAnimInstance, &UCodeRiffleAnim::PlayHealAnimation);
    }
    else
    {
		UE_LOG(LogTemp, Error, TEXT("HealthComponent is nullptr"));
	}
}

void ABaseCharacter::SetReferences()
{
    if (CurrentWeaponClass)
    {
        orientationSocket = GetMesh()->GetSocketTransform("WeaponSocket", ERelativeTransformSpace::RTS_World);
        if(Weapon != nullptr)
            Weapon->Destroy();
        Weapon = GetWorld()->SpawnActor<ABaseWeaponRifle>(CurrentWeaponClass, orientationSocket);
        if (Weapon)
        {
            Weapon->SetOwningPawn(this);
            //Atach to socket
            FName socketName = "WeaponSocket";
            Weapon->SkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, socketName);
            GetMesh()->SetAnimInstanceClass(Weapon->WeaponInfo.WeaponAnimInstance);
        }
        else
        {
			UE_LOG(LogTemp, Error, TEXT("Weapon Incorrectly created"));
        }
    }
    else
    {
		UE_LOG(LogTemp, Error, TEXT("WeaponClass is nullptr"));
    }
}

void ABaseCharacter::SwapWeapon()
{
    if (CurrentWeaponClass == nullptr)
    {
        CurrentWeaponClass = WeaponClass1;
    }
    else
    {
        if (CurrentWeaponClass == WeaponClass1)
        {
			CurrentWeaponClass = WeaponClass2;
		}
        else
        {
			CurrentWeaponClass = WeaponClass1;
		}
    }
    SetReferences();
    BindWeaponAndAnimationEvents();
    Weapon->UpdateAmmo();
}
