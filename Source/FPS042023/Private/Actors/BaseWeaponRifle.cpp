// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseWeaponRifle.h"
#include "../../FPS042023.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Actors/BaseProjectile.h"
#include "CodeRiffleAnim.h"
#include "Components/StaticMeshComponent.h"
#include "Actors/BaseCharacter.h"


//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventDispatcher, AActor*, ParamName);
// Sets default values
ABaseWeaponRifle::ABaseWeaponRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//OwningPawn = Cast<APawn>(GetParentActor());
	/*OwningPawn = Cast<APawn>(GetAttachParentActor());
	if (nullptr == OwningPawn)
	{
		UE_LOG(Game, Error, TEXT("We need a pawn to own this weapon"));
	}*/
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

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


void ABaseWeaponRifle::Shoot()
{
	if (CanShoot())
	{
		// Spawn the projectile at the location of the MuzzleFlashSocket
		TSubclassOf<ABaseProjectile> Projectile = UBaseProjectile;
		FVector SpawnLocation = SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
		FRotator SpawnRotation = OwningPawn->GetActorRotation();
		FTransform SpawnTransform(SpawnRotation, SpawnLocation);
		FActorSpawnParameters Params;
		Params.Owner = OwningPawn->GetController();
		Params.Instigator = OwningPawn;
		ABaseProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ABaseProjectile>(Projectile, SpawnTransform, Params);
		//ABaseProjectile* SpawnedProjectile = GetWorld()->SpawnActor<ABaseProjectile>(Projectile, SpawnLocation, SpawnRotation);

		//Animating = true;

	}
}

void ABaseWeaponRifle::SetOwningPawn(APawn* NewOwningPawn)
{
	OwningPawn = NewOwningPawn;
}

void ABaseWeaponRifle::OnAnimationCompleted()
{
	Animating = false;
}

void ABaseWeaponRifle::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	
}



