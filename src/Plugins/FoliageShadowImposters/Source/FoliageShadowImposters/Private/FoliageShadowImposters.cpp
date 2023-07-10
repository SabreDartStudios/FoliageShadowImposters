// Copyright Epic Games, Inc. All Rights Reserved.

#include "FoliageShadowImposters.h"
#include "FoliageShadowImpostersStyle.h"
#include "FoliageShadowImpostersCommands.h"
#include "EngineUtils.h"
#include "InstancedFoliageActor.h"
#include "FoliageShadowImposterComponent.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName FoliageShadowImpostersTabName("FoliageShadowImposters");

#define LOCTEXT_NAMESPACE "FFoliageShadowImpostersModule"

void FFoliageShadowImpostersModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFoliageShadowImpostersStyle::Initialize();
	FFoliageShadowImpostersStyle::ReloadTextures();

	FFoliageShadowImpostersCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFoliageShadowImpostersCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FFoliageShadowImpostersModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFoliageShadowImpostersModule::RegisterMenus));
}

void FFoliageShadowImpostersModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFoliageShadowImpostersStyle::Shutdown();

	FFoliageShadowImpostersCommands::Unregister();
}

void FFoliageShadowImpostersModule::RemoveAllFoliageShadowImpostersForThisMesh(FString FoliageShadowImposterMeshPath)
{
	for (TActorIterator<AInstancedFoliageActor> FoliageActorIterator(GEditor->GetEditorWorldContext().World()); FoliageActorIterator; ++FoliageActorIterator)
	{
		AInstancedFoliageActor* CurrentFoliageActor = *FoliageActorIterator;
		if (CurrentFoliageActor)
		{
			if (CurrentFoliageActor)
			{
				TArray<UInstancedStaticMeshComponent*> InstancedStaticMeshComponents;
				CurrentFoliageActor->GetComponents(InstancedStaticMeshComponents, true);

				for (UInstancedStaticMeshComponent* ActorComp : InstancedStaticMeshComponents)
				{
					if (UFoliageShadowImposterComponent* InstancedFoliageComp = Cast<UFoliageShadowImposterComponent>(ActorComp))
					{
						if (InstancedFoliageComp->GetStaticMesh().GetPathName() == FoliageShadowImposterMeshPath)
						{
							//UE_LOG(LogTemp, Error, TEXT("Found a UFoliageShadowImposteComponent: %s"), *InstancedFoliageComp->GetName());
							InstancedFoliageComp->UnregisterComponent();
							InstancedFoliageComp->DestroyComponent();
							CurrentFoliageActor->Modify();
						}
					}
				}
			}
		}
	}
}

void FFoliageShadowImpostersModule::AddFoliageShadowImpostersForThisMesh(FString MeshPathToSearchFor, FString FoliageShadowImposterMeshPath)
{
	for (TActorIterator<AInstancedFoliageActor> FoliageActorIterator(GEditor->GetEditorWorldContext().World()); FoliageActorIterator; ++FoliageActorIterator)
	{
		AInstancedFoliageActor* CurrentFoliageActor = *FoliageActorIterator;
		if (CurrentFoliageActor)
		{
			if (CurrentFoliageActor)
			{
				TArray<UInstancedStaticMeshComponent*> InstancedStaticMeshComponents;
				CurrentFoliageActor->GetComponents(InstancedStaticMeshComponents, true);

				for (UInstancedStaticMeshComponent* ActorComp : InstancedStaticMeshComponents)
				{
					if (UFoliageInstancedStaticMeshComponent* InstancedFoliageComp = Cast<UFoliageInstancedStaticMeshComponent>(ActorComp))
					{
						if (InstancedFoliageComp->GetStaticMesh().GetPathName() == MeshPathToSearchFor)
						{
							//UE_LOG(LogTemp, Error, TEXT("Found a UFoliageInstancedStaticMeshComponent: %s"), *InstancedFoliageComp->GetName());
							UFoliageShadowImposterComponent* NewImposterMeshComponent = NewObject<UFoliageShadowImposterComponent>(CurrentFoliageActor,
								UFoliageShadowImposterComponent::StaticClass(),
								NAME_None, RF_Transactional);

							CurrentFoliageActor->AddInstanceComponent(NewImposterMeshComponent);
							NewImposterMeshComponent->RegisterComponent();
							NewImposterMeshComponent->AttachToComponent(CurrentFoliageActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
							UStaticMesh* ImposterMeshToUse = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *FoliageShadowImposterMeshPath));
							NewImposterMeshComponent->SetStaticMesh(ImposterMeshToUse);
							NewImposterMeshComponent->SetMobility(EComponentMobility::Static);
							CurrentFoliageActor->Modify();

							FTransform InstanceTransform;
							for (int32 FoliageInstanceIndex = InstancedFoliageComp->GetInstanceCount() - 1; FoliageInstanceIndex >= 0; FoliageInstanceIndex--)
							{
								InstancedFoliageComp->GetInstanceTransform(FoliageInstanceIndex, InstanceTransform, true);
								//UE_LOG(LogTemp, Warning, TEXT("Found a foliage instance at: %s with rotation: %s and scale: %s"), *InstanceTransform.GetLocation().ToString(), *InstanceTransform.GetRotation().ToString(), *InstanceTransform.GetScale3D().ToString());
								NewImposterMeshComponent->AddInstance(InstanceTransform, true);
							}
						}
					}
				}
			}
		}
	}
}

void FFoliageShadowImpostersModule::PluginButtonClicked()
{
	FString PathToFoliageShadowImposterReplacementDataTable;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("PathToFoliageShadowImposterReplacementDataTable"),
		PathToFoliageShadowImposterReplacementDataTable,
		GGameIni
	);
	//UE_LOG(LogTemp, Error, TEXT("Loaded parth from Config File: %s"), *PathToFoliageShadowImposterReplacementDataTable);

	UDataTable* FoliageShadowImposterReplacementDataTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *PathToFoliageShadowImposterReplacementDataTable));
	for (auto RowMapRow : FoliageShadowImposterReplacementDataTable->GetRowMap())
	{
		FFoliageShadowImposterReplacementRow* FoliageShadowImposterReplacementRow = reinterpret_cast<FFoliageShadowImposterReplacementRow*>(RowMapRow.Value);

		if (FoliageShadowImposterReplacementRow->bShouldReplace)
		{
			RemoveAllFoliageShadowImpostersForThisMesh(FoliageShadowImposterReplacementRow->FoliageSahdowImposterMesh->GetPathName());

			AddFoliageShadowImpostersForThisMesh(FoliageShadowImposterReplacementRow->OriginalFoliageMesh->GetPathName(), 
				FoliageShadowImposterReplacementRow->FoliageSahdowImposterMesh->GetPathName());
		}
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText(LOCTEXT("PluginButtonDialogText", "Foliage Shadow Imposters have been added!")));
}

void FFoliageShadowImpostersModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFoliageShadowImpostersCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFoliageShadowImpostersCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFoliageShadowImpostersModule, FoliageShadowImposters)