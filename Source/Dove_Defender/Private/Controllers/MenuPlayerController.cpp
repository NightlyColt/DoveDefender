// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/MenuPlayerController.h"
#include "Widgets/MainMenu.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
void AMenuPlayerController::BeginPlay()
{
	auto widget = CreateWidget<UMainMenu>(this, WidgetClass);
	widget->AddToViewport(0);

	UWidgetBlueprintLibrary::SetInputMode_UIOnly(this, widget, true);
	SetShowMouseCursor(true);
}
