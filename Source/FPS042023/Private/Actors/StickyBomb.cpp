// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyBomb.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Actors/Effects/Effects_Fire.h"

AStickyBomb::AStickyBomb()
{
	//Collision->SetSphereRadius(50.f);
	DamageRadius = 400.f;
	Damage = 35.f;
}

void AStickyBomb::HandleCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//cast other component as skeletal mesh
	USkeletalMeshComponent* SkeletalMesh = Cast<USkeletalMeshComponent>(OtherComp);

	if (nullptr != SkeletalMesh)
	{
		AttachToComponent(SkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, SweepResult.BoneName);
		Movement->StopMovementImmediately();
		GetWorldTimerManager().ClearTimer(TimerHandle_DestroyProjectile);
	}
	else
	{
		switch (OtherComp->GetCollisionObjectType())
		{
			case ECollisionChannel::ECC_WorldStatic:
				Movement->StopMovementImmediately();
				GetWorldTimerManager().ClearTimer(TimerHandle_DestroyProjectile);
				TeleportTo(SweepResult.Location, GetActorRotation());
				break;

			case ECollisionChannel::ECC_WorldDynamic:
				break;

			case ECollisionChannel::ECC_Pawn:
				break;

			default:
				break;
		}
	}
}

void AStickyBomb::SpecialPower()
{
	Super::SpecialPower();
	//spawn fire effect
	if (nullptr != FireEffect)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		AEffects_Fire* Fire = GetWorld()->SpawnActor<AEffects_Fire>(FireEffect, GetActorLocation(), GetActorRotation(), SpawnParams);
	}

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, nullptr, TArray<AActor*>(), this, GetInstigatorController(), false, ECC_Visibility);
	Destroy();
}

