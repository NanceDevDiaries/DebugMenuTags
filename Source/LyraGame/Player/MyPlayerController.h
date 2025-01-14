// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraPlayerController.h"
#include "MyPlayerController.generated.h"

struct FGameplayTagContainer;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class LYRAGAME_API AMyPlayerController : public ALyraPlayerController
{
	GENERATED_BODY()

protected:
	virtual void OnPlayerStateChanged() override;

#if !UE_BUILD_SHIPPING
	void OnDebugGameplayTagAdded(const FGameplayTag& GameplayTag);
	void OnDebugGameplayTagRemoved(const FGameplayTag& GameplayTag);

	void ApplyDebugGameplayTags(const FGameplayTagContainer& TagsToAdd, const FGameplayTagContainer& TagsToRemove);
#endif // #if !UE_BUILD_SHIPPING
	
	// Applies DynamicTagGameplayEffect that hold the tags, better than loosely added tags
	UFUNCTION(Server, Reliable)
	void ServerApplyDebugGameplayTags(const FGameplayTagContainer& TagsToAdd, const FGameplayTagContainer& TagsToRemove);

};
