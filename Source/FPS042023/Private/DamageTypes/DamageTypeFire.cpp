// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageTypes/DamageTypeFire.h"
#include "Widgets/EffectComponent.h"

UDamageTypeFire::UDamageTypeFire()
{
}

void UDamageTypeFire::PlayEffects(AActor* DamagedActor, AActor* DamageCauser)
{
	UEffectComponent* EffectComponent = DamagedActor->FindComponentByClass<UEffectComponent>();
	if (EffectComponent)
	{
		EffectComponent->StartEffect(EDamageTypes::Fire, DamageCauser);
	}
}
