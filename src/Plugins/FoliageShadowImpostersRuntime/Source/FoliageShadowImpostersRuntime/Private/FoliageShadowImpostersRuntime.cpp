// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoliageShadowImpostersRuntime.h"
#include "EngineUtils.h"
#include "InstancedFoliageActor.h"
#include "FoliageShadowImposterComponent.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

static const FName FoliageShadowImpostersTabName("FoliageShadowImposters");

#define LOCTEXT_NAMESPACE "FFoliageShadowImpostersModule"

void FFoliageShadowImpostersRuntimeModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFoliageShadowImpostersRuntimeModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFoliageShadowImpostersRuntimeModule, FoliageShadowImpostersRuntime)