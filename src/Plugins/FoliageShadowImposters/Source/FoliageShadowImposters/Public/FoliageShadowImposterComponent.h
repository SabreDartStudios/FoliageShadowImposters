// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "FoliageShadowImposterComponent.generated.h"

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

/**
 * 
 */
UCLASS()
class FOLIAGESHADOWIMPOSTERS_API UFoliageShadowImposterComponent : public UFoliageInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFoliageShadowImposterComponent();

	
};
