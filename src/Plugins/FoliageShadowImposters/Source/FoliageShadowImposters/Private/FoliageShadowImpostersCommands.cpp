// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoliageShadowImpostersCommands.h"

#define LOCTEXT_NAMESPACE "FFoliageShadowImpostersModule"

void FFoliageShadowImpostersCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "FoliageShadowImposters", "Add Foliage Shadow Imposters", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
