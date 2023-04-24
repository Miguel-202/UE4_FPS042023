// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MyUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Kismet/GameplayStaticsTypes.h>
#include "Blueprint/SlateBlueprintLibrary.h" 
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

//TODO DELETE AFTER DEBUG
#include <DrawDebugHelpers.h>



UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetHealthBarPercent(1.0);
}

UMyUserWidget::~UMyUserWidget()
{
	RemoveFromParent();
}

void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FVector Start;
	GetLinePoints(Start, HitScanEnd);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetOwningPlayerPawn());

	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = {
	UEngineTypes::ConvertToObjectType(ECC_WorldStatic),
	UEngineTypes::ConvertToObjectType(ECC_Pawn)
	};


	FHitResult HitResult;
	IsHitScanValid = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		Start,
		HitScanEnd,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true
	);

	if (IsHitScanValid)
	{
		HitScanLocation = HitResult.Location;
		AActor* HitActor = HitResult.GetActor();
		if (nullptr != HitActor)
		{
			if (HitActor->ActorHasTag("Enemy"))
			{
				SetMaterialColor(DangerColor, currentReticleIndex);
			}
			else
			{
				SetMaterialColor(WarningColor, currentReticleIndex);
			}
		}
		else
		{
			SetMaterialColor(SafeColor, currentReticleIndex);
		}
	}
	else
	{
		SetMaterialColor(Defaultcolor, currentReticleIndex);
	}
}

void UMyUserWidget::RunOnBeginPlay()
{	
	currentReticleIndex = 0;
	ReticleSwitcher->SetActiveWidgetIndex(currentReticleIndex);
	for (int i = 0; i < 2; i++)
	{
		Reticle = Cast<UImage>(ReticleSwitcher->GetWidgetAtIndex(i));
		// Cast the brush to a UMaterialInterface
		UMaterialInterface* MaterialInterface = Cast<UMaterialInterface>(Reticle->Brush.GetResourceObject());
		// Create a dynamic material instance
		if (MaterialInterface)
		{
			DynamicReticleMaterial[i] = UMaterialInstanceDynamic::Create(MaterialInterface, this);
		}
		Reticle->SetBrushFromMaterial(DynamicReticleMaterial[i]);
	}

	AddToViewport();
	OnUpdateHealth.AddDynamic(this, &UMyUserWidget::SetHealthBarPercent);
	SetMaterialColor(DangerColor, currentReticleIndex);

	
}

void UMyUserWidget::SetHealthBarPercent(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void UMyUserWidget::SetMaterialColor(FLinearColor Color, int32 materialIndex)
{
	if (DynamicReticleMaterial[materialIndex])
	{
		DynamicReticleMaterial[materialIndex]->SetVectorParameterValue(ColorParamName, Color);
	}
}

void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Get the widgets
	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HealthBar")));
	ReticleSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("ReticleSwitcher")));
}

void UMyUserWidget::GetLinePoints(FVector& Start, FVector& End)
{
	APlayerController* PC = GetOwningPlayer();
    if (PC)
    {
		FVector2D LocalPosition = FVector2D::ZeroVector;
		FVector2D UnusedViewportPosition;
		USlateBlueprintLibrary::LocalToViewport(Reticle->GetWorld(), Cast<UImage>(ReticleSwitcher->GetWidgetAtIndex(currentReticleIndex))->GetCachedGeometry(), FVector2D(0.5f, 0.5f), LocalPosition, UnusedViewportPosition);
		FVector2D ReticleSize = Reticle->GetCachedGeometry().GetLocalSize() * 0.5f;
		LocalPosition += FVector2D(ReticleSize.X, ReticleSize.Y);

		FVector WorldStart, WorldDirection;
		PC->DeprojectScreenPositionToWorld(LocalPosition.X, LocalPosition.Y, WorldStart, WorldDirection);
		Start = WorldStart;

		// Trace from the reticle's position towards the direction to find the first blocking hit
		FHitResult HitResult;
		FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(UMyWidget), true, PC->GetPawn());
		End = WorldStart + (WorldDirection * 100000); // Set the end point far enough to cover the screen
		GetWorld()->LineTraceSingleByChannel(HitResult, WorldStart, End, ECC_Visibility, TraceParams);

		// If the hit was blocking, then the end point is the impact point, otherwise it is the original end point
		End = HitResult.bBlockingHit ? HitResult.ImpactPoint : End;

    }
}

void UMyUserWidget::GetAimedPoint(FVector& HitLocation, FVector& EndPoint, bool& IsHitValid)
{
	HitLocation = HitScanLocation;
	EndPoint = HitScanEnd;
	IsHitValid = IsHitScanValid;
}

void UMyUserWidget::SetAmmoText(float CurrentAmmo, float MaxAmmo)
{
	FString CurrentAmmoString = FString::SanitizeFloat(CurrentAmmo);
	FString MaxAmmoString = FString::SanitizeFloat(MaxAmmo);

	FString AmmoString = FString::Printf(TEXT("%s / %s"), *CurrentAmmoString, *MaxAmmoString);
	if (CurrentAmmoText != nullptr)
	{
		CurrentAmmoText->SetText(FText::FromString(CurrentAmmoString));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Should reload but current amo text is null")));
	}
	if (MaxAmmoText != nullptr)
	{
		MaxAmmoText->SetText(FText::FromString(MaxAmmoString));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Should reload but max amo text is null")));
	}
}

void UMyUserWidget::SetIconSwitcher(int32 WeaponIndex)
{
	//set active widget index to the index of the weapon
	IconSwitcher->SetActiveWidgetIndex(WeaponIndex);
	ReticleSwitcher->SetActiveWidgetIndex(WeaponIndex);
	currentReticleIndex = WeaponIndex;
	Reticle = Cast<UImage>(ReticleSwitcher->GetWidgetAtIndex(WeaponIndex));
	//Print to screen the current image in the reticle switcher 
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Current reticle index is %d"), ReticleSwitcher->GetActiveWidget()));
}





