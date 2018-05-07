// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Practica1_kaspersGameMode.h"
#include "Practica1_kaspersCharacter.h"
#include "UObject/ConstructorHelpers.h"

APractica1_kaspersGameMode::APractica1_kaspersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
