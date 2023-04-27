// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MyUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "Materials/MaterialInterface.h"
#include <Blueprint/SlateBlueprintLibrary.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Components/TextBlock.h"
#include <Kismet/KismetTextLibrary.h>
#include "Components/WidgetSwitcher.h"
#include "Materials/MaterialInstanceDynamic.h"


UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}



void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	auto Material = Cast<UMaterialInterface>(Reticle->Brush.GetResourceObject());
	if (Material)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
		Reticle->SetBrushFromMaterial(DynamicMaterial);
		SetMaterialColor(DefaultColor);
	}
	if (DynamicMaterial == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "NOT SET");

	}
	else
	{
		DynamicMaterials.Add(DynamicMaterial);
		auto Image = Cast<UImage>(ReticleSwitcher->GetWidgetAtIndex(1));
		if (Image)
		{
			auto Mat = Cast<UMaterialInterface>(Image->Brush.GetResourceObject());
			auto dynMat = UMaterialInstanceDynamic::Create(Mat, this);
			DynamicMaterials.Add(dynMat);
			Image->SetBrushFromMaterial(dynMat);
		}
		else
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Image Not Found");


	}
	CurrentAmmo->SetText(FText::FromString(TEXT("100")));
	MaxAmmo->SetText(FText::FromString(TEXT("100")));
}
bool UMyUserWidget::GetAimedPoint(bool& _Valid, FVector& _HitLocation, FVector& _EndPoint) const
{
	_Valid = ValidHit;
	_HitLocation = HitLocation;
	_EndPoint = EndPoint;
	return true;
}
void UMyUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	FVector Start;
	FVector End;
	GetLinePoints(Start, End);
	TArray<TEnumAsByte<EObjectTypeQuery>> Trace;
	TArray<AActor*> Ignore;
	Trace.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	Trace.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	Ignore.Add(GetOwningPlayer());
	FHitResult hit;
	ValidHit = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), Start, End, Trace, false, Ignore, EDrawDebugTrace::None, hit, true);
	if (ValidHit)
	{
		HitLocation = hit.Location;
		if (Cast<APawn>(hit.Actor))
		{
			SetMaterialColor(DangerColor);
		}
		else
			SetMaterialColor(DefaultColor);
	}
	else
	{
		EndPoint = End;
		SetMaterialColor(DefaultColor);
	}

}

void UMyUserWidget::SetMaterialColor(FLinearColor Color)
{
	DynamicMaterial->SetVectorParameterValue("Color", Color);
}

bool UMyUserWidget::GetLinePoints(FVector& _StartPoint, FVector& _EndPoint) const
{
	FGeometry tempGeo = Reticle->GetCachedGeometry();
	FVector2D PixelLocation;
	FVector2D View;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), tempGeo, FVector2D(0, 0), PixelLocation, View);
	FVector2D Result = (USlateBlueprintLibrary::GetAbsoluteSize(tempGeo) * 0.5) + PixelLocation;
	FVector WPosition;
	FVector WDirection;
	GetOwningPlayer()->DeprojectScreenPositionToWorld(Result.X, Result.Y, WPosition, WDirection);
	_StartPoint = WPosition;
	_EndPoint = WPosition + (WDirection * 100000);
	return true;
}


void UMyUserWidget::SetHealth(float ratio)
{
	Health->SetPercent(ratio);
}

void UMyUserWidget::SetAmmo(float Current, float Max)
{
	CurrentAmmo->SetText(UKismetTextLibrary::Conv_FloatToText(Current, ERoundingMode::ToZero));
	MaxAmmo->SetText(UKismetTextLibrary::Conv_FloatToText(Max, ERoundingMode::ToZero));
}

void UMyUserWidget::SetIconIndex(int WeaponIndex)
{
	IconWeaponSwitcher->SetActiveWidgetIndex(WeaponIndex);
	ReticleSwitcher->SetActiveWidgetIndex(WeaponIndex);
	DynamicMaterial = DynamicMaterials[WeaponIndex];
}
