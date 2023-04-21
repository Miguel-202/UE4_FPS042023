// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Pickups/BasePickup.h"
#include "Components/BoxComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	SetRootComponent(CollisionBox);

	CollisionBox->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
	CollisionBox->SetCollisionProfileName("Custom");
	CollisionBox->SetGenerateOverlapEvents(true);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::HandleCollision);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::HandleCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherComponent)
	{
		// Check if the other actor is the owning pawn of the projectile
		APawn* OwningPawn = Cast<APawn>(GetInstigator());
		if (OwningPawn && OtherActor == OwningPawn)
		{
			// Ignore the collision with the owning pawn
			return;
		}
		else
		{
			// Check if the other actor is a pawn
			APawn* OtherPawn = Cast<APawn>(OtherActor);
			if (OtherPawn)
			{
				// Check if the other pawn is the player
				ABasePlayer* Player = Cast<ABasePlayer>(OtherPawn);
				if (Player)
				{
					HandlePostPickup(Player);
				}
			}
		}

	}
}

void ABasePickup::HandlePostPickup(ABasePlayer* Player)
{
	Destroy();
}

