// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/StickyGun.h"
//#include "Actors/StickyBomb.h"

AStickyGun::AStickyGun()
{
	MaxAmmo = 5;
	CurrentAmmo = MaxAmmo;
}

ABaseProjectile* AStickyGun::Shoot()
{
	ABaseProjectile* Projectile = Super::Shoot();
	if (nullptr != Projectile)
	{
		//add to vector of projectiles
		ProjectilesShoted.Add(Projectile);
	}
	return Projectile;
}

void AStickyGun::HandleSpecialPower()
{
	Super::HandleSpecialPower();
	for (ABaseProjectile* Projectile : ProjectilesShoted)
	{
		Projectile->SpecialPower();
	}
	ProjectilesShoted.Empty();
}
