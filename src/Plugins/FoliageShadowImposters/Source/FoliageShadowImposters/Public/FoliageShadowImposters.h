// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "FoliageShadowImposters.generated.h"

class FToolBarBuilder;
class FMenuBuilder;

USTRUCT(BlueprintType)
struct FFoliageShadowImposterReplacementRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	/** Should we add the Foliage Shadow Imposter Mesh when we run the plugin process? **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bShouldReplace;

	/** This is the foliage mesh we are searching for to add Foliage Shadow Imposters for. **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* OriginalFoliageMesh;

	/** This is the Foliage Shadow Imposter mesh.  This should NOT have WPO materials and should be a low poly mesh for shadow casting. **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* FoliageSahdowImposterMesh;

};

class FFoliageShadowImpostersModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
private:

	void RemoveAllFoliageShadowImpostersForThisMesh(FString FoliageShadowImposterMeshPath);
	void AddFoliageShadowImpostersForThisMesh(FString MeshPathToSearchFor, FString FoliageShadowImposterMeshPath);
	void RegisterMenus();


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
