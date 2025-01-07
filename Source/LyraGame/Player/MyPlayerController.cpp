// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Development/MyGameplayDebugSettings.h"
#include "Settings/MySettingsLocal.h"

void AMyPlayerController::OnPlayerStateChanged()
{
	// TODO not sure if we want to omit from shipping build, maybe just the UI menu?
#if !UE_BUILD_SHIPPING 
	// hook up to debug loose gameplay tags in the settings, for nicer debug experience on granting/disabling GAs and GEs
	// TODO do I need to unbind and remove the tags?
	if (IsLocalPlayerController() && GetLyraPlayerState())
	{
		UMySettingsLocal::Get()->OnLooseGameplayTagAdded.AddUObject(this, &AMyPlayerController::OnDebugGameplayTagAdded);
		UMySettingsLocal::Get()->OnLooseGameplayTagRemoved.AddUObject(this, &AMyPlayerController::OnDebugGameplayTagRemoved);
		if (const UMyGameplayDebugSettings* GameplayDebugSettings = GetDefault<UMyGameplayDebugSettings>())
		{
			FGameplayTagContainer TagsToLooselyAdd;
			for (const auto& AddedSetting : GameplayDebugSettings->DebugGameplayTags)
			{
				if(UMySettingsLocal::Get()->GetWantsToAddGameplayTag(AddedSetting.GameplayTag))
				{
					TagsToLooselyAdd.AddTag(AddedSetting.GameplayTag);
				}
			}
			if (!TagsToLooselyAdd.IsEmpty())
			{
				if (HasAuthority())
				{
					ApplyDebugGameplayTags(TagsToLooselyAdd, FGameplayTagContainer());
				}
				else
				{
					ServerApplyDebugGameplayTags(TagsToLooselyAdd, FGameplayTagContainer());
				}
			}
		}
	}
#endif // #if !UE_BUILD_SHIPPING
}

#if !UE_BUILD_SHIPPING
void AMyPlayerController::OnDebugGameplayTagAdded(const FGameplayTag& GameplayTag)
{
	if (HasAuthority())
	{
		ApplyDebugGameplayTags(FGameplayTagContainer(GameplayTag), FGameplayTagContainer());
	}
	else
	{
		ServerApplyDebugGameplayTags(FGameplayTagContainer(GameplayTag), FGameplayTagContainer());
	}
}

void AMyPlayerController::OnDebugGameplayTagRemoved(const FGameplayTag& GameplayTag)
{
	if (HasAuthority())
	{
		ApplyDebugGameplayTags(FGameplayTagContainer(), FGameplayTagContainer(GameplayTag));
	}
	else
	{
		ServerApplyDebugGameplayTags(FGameplayTagContainer(), FGameplayTagContainer(GameplayTag));
	}
}

void AMyPlayerController::ApplyDebugGameplayTags(const FGameplayTagContainer& TagsToAdd,
	const FGameplayTagContainer& TagsToRemove)
{
	ULyraAbilitySystemComponent* LyraAbilitySystem = GetLyraAbilitySystemComponent();
	for (const FGameplayTag& TagToAdd : TagsToAdd)
	{
		LyraAbilitySystem->AddDynamicTagGameplayEffect(TagToAdd);
	}
	for (const FGameplayTag& TagToRemove : TagsToRemove)
	{
		LyraAbilitySystem->RemoveDynamicTagGameplayEffect(TagToRemove);
	}
}
#endif // #if !UE_BUILD_SHIPPING

// Create or remove gameplay effects
void AMyPlayerController::ServerApplyDebugGameplayTags_Implementation(const FGameplayTagContainer& TagsToAdd,
	const FGameplayTagContainer& TagsToRemove)
{
#if !UE_BUILD_SHIPPING
	ApplyDebugGameplayTags(TagsToAdd, TagsToRemove);
#endif // #if !UE_BUILD_SHIPPING
}
