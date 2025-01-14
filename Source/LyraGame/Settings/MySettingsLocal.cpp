// Fill out your copyright notice in the Description page of Project Settings.


#include "MySettingsLocal.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
UMySettingsLocal::UMySettingsLocal()
{
}
PRAGMA_ENABLE_DEPRECATION_WARNINGS

UMySettingsLocal* UMySettingsLocal::Get()
{
	return GEngine ? CastChecked<UMySettingsLocal>(GEngine->GetGameUserSettings()) : nullptr;
}

void UMySettingsLocal::AddOrUpdateLooselyAddedGameplayTag(const FGameplayTag& GameplayTag, bool Added)
{
	if (Added)
	{
		CustomLooselyAddedGameplayTag.Add(GameplayTag);
		OnLooseGameplayTagAdded.Broadcast(GameplayTag);
	}
	else
	{
		CustomLooselyAddedGameplayTag.Remove(GameplayTag);
		OnLooseGameplayTagRemoved.Broadcast(GameplayTag);
	}
}

bool UMySettingsLocal::GetWantsToAddGameplayTag(const FGameplayTag& GameplayTag) const
{
	return CustomLooselyAddedGameplayTag.Contains(GameplayTag);
}
