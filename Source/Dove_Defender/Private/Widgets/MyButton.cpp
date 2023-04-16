// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MyButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

UMyButton::UMyButton(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UMyButton::NativePreConstruct()
{
	BackgroundButton->OnClicked.AddDynamic(this, &UMyButton::HandleOnButtonClicked);
	Info->SetText(ButtonText);
}

void UMyButton::HandleOnButtonClicked()
{
	OnButtonClick.Broadcast();
}
