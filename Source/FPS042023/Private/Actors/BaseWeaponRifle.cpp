// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeaponRifle.h"
#include "../../FPS042023.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Actors/BaseProjectile.h"
#include "CodeRiffleAnim.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/BaseCharacter.h"
#include "Widgets/MyUserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include <Kismet/KismetMathLibrary.h>


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher, AActor*, ParamName);
// Sets default values
ABaseWeaponRifle::ABaseWeaponRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	MaxAmmo = 10;
	CurrentAmmo = MaxAmmo;

}

// Called when the game starts or when spawned
void ABaseWeaponRifle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseWeaponRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseWeaponRifle::CanReload()
{
	if (Animating)
	{
		return false;
	}
	else
	{
		Animating = true;
		StartReloadDelegate.Broadcast();
	}
	return true;
}

bool ABaseWeaponRifle::CanShoot()
{
	return CurrentAmmo > 0 && !Animating;
}

void ABaseWeaponRifle::Shoot()
{
	if (CanShoot())
	{
		UseAmmo();
		// Spawn the projectile at the location of the MuzzleFlashSocket
		TSubclassOf<ABaseProjectile> Projectile = UBaseProjectile;
		FVector SpawnLocation = SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
		FRotator SpawnRotation = GetShootRotation();
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);
		FActorSpawnParameters Params;
		Params.Owner = OwningPawn->GetController();
		Params.Instigator = OwningPawn;
		ABaseProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ABaseProjectile>(Projectile, SpawnTransform, Params);
		//ABaseProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ABaseProjectile>(Projectile, SpawnLocation, SpawnRotation);

		Animating = true;

	}
}

void ABaseWeaponRifle::Reload()
{
	CurrentAmmo = MaxAmmo;
	AmmoChangeDelegate.Broadcast(CurrentAmmo, MaxAmmo);
}

void ABaseWeaponRifle::UseAmmo()
{
	CurrentAmmo = FMath::Clamp(CurrentAmmo - 1, 0.0f, MaxAmmo);
	AmmoChangeDelegate.Broadcast(CurrentAmmo, MaxAmmo);

}

void ABaseWeaponRifle::SetOwningPawn(APawn* NewOwningPawn)
{
	OwningPawn = NewOwningPawn;
}

void ABaseWeaponRifle::OnAnimationCompleted()
{
	Animating = false;
	CharacterActionEndedDelegate.Broadcast();
}

FRotator ABaseWeaponRifle::GetShootRotation()
{
	FRotator ShootRotation = OwningPawn->GetController()->GetControlRotation();
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UMyUserWidget::StaticClass(), false);
	if (FoundWidgets.Num() > 0)
	{
		for (UUserWidget* Widget : FoundWidgets)
		{
			UMyUserWidget* MyWidget = Cast<UMyUserWidget>(Widget);
			if (MyWidget->GetOwningPlayerPawn() == OwningPawn)
			{
				FVector AimedPoint; FVector EndPoint; bool Hit; FVector Destination;
				MyWidget->GetAimedPoint(AimedPoint, EndPoint, Hit);
				if (Hit)
				{
					Destination = AimedPoint;
				}
				else
				{
					Destination = EndPoint;
				}
				ShootRotation = ShootRotation = UKismetMathLibrary::MakeRotFromX(Destination - SkeletalMesh->GetSocketLocation("MuzzleFlashSocket"));
			}
			else
			{
				ShootRotation = OwningPawn->GetController()->GetControlRotation();
			}
		}
	}
	else
	{
		ShootRotation = OwningPawn->GetController()->GetControlRotation();
	}
	return ShootRotation;
}

void ABaseWeaponRifle::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	
}




