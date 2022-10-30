// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoliageShadowImpostersStyle.h"
#include "FoliageShadowImposters.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FFoliageShadowImpostersStyle::StyleInstance = nullptr;

void FFoliageShadowImpostersStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FFoliageShadowImpostersStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FFoliageShadowImpostersStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("FoliageShadowImpostersStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FFoliageShadowImpostersStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("FoliageShadowImpostersStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("FoliageShadowImposters")->GetBaseDir() / TEXT("Resources"));

	Style->Set("FoliageShadowImposters.PluginAction", new IMAGE_BRUSH_SVG(TEXT("FSIButtonIcon"), Icon20x20));
	return Style;
}

void FFoliageShadowImpostersStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FFoliageShadowImpostersStyle::Get()
{
	return *StyleInstance;
}
