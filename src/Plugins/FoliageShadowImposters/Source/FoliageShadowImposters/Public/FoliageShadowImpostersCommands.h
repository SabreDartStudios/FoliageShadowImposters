// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FoliageShadowImpostersStyle.h"

class FFoliageShadowImpostersCommands : public TCommands<FFoliageShadowImpostersCommands>
{
public:

	FFoliageShadowImpostersCommands()
		: TCommands<FFoliageShadowImpostersCommands>(TEXT("FoliageShadowImposters"), NSLOCTEXT("Contexts", "FoliageShadowImposters", "FoliageShadowImposters Plugin"), NAME_None, FFoliageShadowImpostersStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
