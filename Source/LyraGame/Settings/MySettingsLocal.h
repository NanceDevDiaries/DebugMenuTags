// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LyraSettingsLocal.h"
#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "MySettingsLocal.generated.h"

/**
 * UMySettingsLocal
 */
UCLASS()
class UMySettingsLocal : public ULyraSettingsLocal
{
	GENERATED_BODY()
	
public:

	UMySettingsLocal();

	static UMySettingsLocal* Get();

public:
	// @Game-Change add a section for easy gameplay testing,
	// used in the settings UI menu for developers to quickly add specific loose gameplay tags for testing.
	//////////////////////////////////////////////////////////////////
	// Debug tags to add, for easy gameplay testing
	
	UFUNCTION()
	TArray<FGameplayTag> GetCustomLooselyAddedGameplayTag() const { return CustomLooselyAddedGameplayTag; }
	
	DECLARE_EVENT_OneParam(ULyraSettingsLocal, FDebugLooseGameplayTagDelegate, const FGameplayTag& /*Config*/);
	
	FDebugLooseGameplayTagDelegate OnLooseGameplayTagAdded;
	FDebugLooseGameplayTagDelegate OnLooseGameplayTagRemoved;
	
	void AddOrUpdateLooselyAddedGameplayTag(const FGameplayTag& GameplayTag, bool Added);
	bool GetWantsToAddGameplayTag(const FGameplayTag& GameplayTag) const;
	
private:
	/** Array of custom loosely added tags that have been set by the player. Empty by default. */
	UPROPERTY(config)
	TArray<FGameplayTag> CustomLooselyAddedGameplayTag;

	/** @Game-Change end Implement debug for adding loosely added gameplay tags **/
};
