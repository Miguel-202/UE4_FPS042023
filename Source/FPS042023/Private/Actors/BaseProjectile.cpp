// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BaseProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actors/BaseCharacter.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(10.f);
	//SetRootComponent(Collision);
	Collision->SetCollisionProfileName("Custom");
	Collision->SetGenerateOverlapEvents(true);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::HandleCollision);
	RootComponent = Collision;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName("BlockAllDynamic");

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1800.0f;
	Movement->MaxSpeed = 2000.0f;
	Movement->ProjectileGravityScale = 0.0f;
	Damage = 10.0f;
	//Movement->bRotationFollowsVelocity = true;
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_DestroyProjectile, [this]()
		{
			Destroy();
		}, 3.f, false);
	Mesh->SetWorldScale3D(FVector(.15f, .15f, .15f));
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::HandleCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			//Cast to the base character and do damage
			UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), UDamageType::StaticClass());
			 
			// Destroy the projectile
			DestroyProjectile();
		}

	}
	
}

void ABaseProjectile::DestroyProjectile()
{
	Destroy();
}

void ABaseProjectile::SpecialPower()
{
}

