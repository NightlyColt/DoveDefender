// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DOVE_DEFENDER_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UMyUserWidget(const FObjectInitializer& ObjectInitializer);
protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	void SetMaterialColor(FLinearColor Color);
	bool GetLinePoints(FVector& _StartPoint, FVector& _EndPoint) const;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* Health;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Reticle;

	UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor DefaultColor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor DangerColor;
	FVector EndPoint;
	FVector HitLocation;
	bool ValidHit;

public:
	void NativeConstruct() override;
	bool GetAimedPoint(bool& _Valid, FVector& _HitLocation, FVector& _EndPoint) const;
	UFUNCTION(BlueprintCallable)
	void SetHealth(float ratio);
};
