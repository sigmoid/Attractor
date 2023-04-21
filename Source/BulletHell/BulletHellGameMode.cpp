// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "BulletHellGameMode.h"
#include "BulletHellPawn.h"
#include "Blueprint/UserWidget.h"

ABulletHellGameMode::ABulletHellGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ABulletHellPawn::StaticClass();
}

void ABulletHellGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}

void ABulletHellGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}