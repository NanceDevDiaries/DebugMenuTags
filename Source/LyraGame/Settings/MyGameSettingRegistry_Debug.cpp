// Copyright (c) 2025, NanceDevDiaries

#include "GameSettingCollection.h"
#include "MyGameSettingRegistry.h"
#include "NativeGameplayTags.h"
#if !UE_BUILD_SHIPPING
#include "CustomSettings/MySettingValueDiscrete_GameplayTagBool.h"
#endif // #if !UE_BUILD_SHIPPING
#include "Development/MyGameplayDebugSettings.h"
#include "Player/LyraLocalPlayer.h"

#define LOCTEXT_NAMESPACE "Lyra"

#if !UE_BUILD_SHIPPING
UGameSettingCollection* UMyGameSettingRegistry::InitializeDebugSettings(ULyraLocalPlayer* InLocalPlayer)
{
	UGameSettingCollection* DebugCollection = NewObject<UGameSettingCollection>();
	DebugCollection->SetDevName(TEXT("DebugCollection"));
	DebugCollection->SetDisplayName(LOCTEXT("DebugCollection_Name", "Debug"));
	DebugCollection->Initialize(InLocalPlayer);

	// Loose Gameplay Tags
	////////////////////////////////////////////////////////////////////////////////////
	{
		UGameSettingCollection* LooseTagsCollection = NewObject<UGameSettingCollection>();
		LooseTagsCollection->SetDevName(TEXT("LooseTagsCollection"));
		LooseTagsCollection->SetDisplayName(LOCTEXT("LooseTagsCollection_Name", "Loose Tags"));
		DebugCollection->AddSetting(LooseTagsCollection);

		static TSet<FName> AddedSettings;
		AddedSettings.Reset();
			
		//----------------------------------------------------------------------------------
		{
			if (const UMyGameplayDebugSettings* GameplayDebugSettings = GetDefault<UMyGameplayDebugSettings>())
			{
				for (const auto& DebugGameplayTag : GameplayDebugSettings->DebugGameplayTags)
				{
					// Make sure that we cannot add two settings with the same FName for saving purposes
					if (AddedSettings.Contains(DebugGameplayTag.GameplayTag.GetTagName()))
					{
						UE_LOG(LogLyraGameSettingRegistry, Warning,
						       TEXT(
							       "A setting with the tag name '%s' has already been added! Please remove duplicate tags."
						       ), *DebugGameplayTag.GameplayTag.ToString());
						continue;
					}

					UMySettingValueDiscrete_GameplayTagBool* LooseGameplayTagSetting = NewObject<UMySettingValueDiscrete_GameplayTagBool>();

					LooseGameplayTagSetting->SetGameplayTagData(DebugGameplayTag.GameplayTag, DebugGameplayTag.OptionalDisplayText);
					LooseTagsCollection->AddSetting(LooseGameplayTagSetting);
					AddedSettings.Add(DebugGameplayTag.GameplayTag.GetTagName());
				}
			}
		}
		//----------------------------------------------------------------------------------
	}

	return DebugCollection;
}
#endif // #if !UE_BUILD_SHIPPING

#undef LOCTEXT_NAMESPACE
