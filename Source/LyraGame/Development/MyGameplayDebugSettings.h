// Copyright (c) 2025, NanceDevDiaries

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "MyGameplayDebugSettings.generated.h"

USTRUCT(BlueprintType)
struct FDebugTagDisplay
{
	GENERATED_BODY()

public:
	// Gameplay tag to add to the player loosely, through a GE
	UPROPERTY(EditAnywhere)
	FGameplayTag GameplayTag;

	// Text to display if defined instead of the gameplay tag. More human readable!
	UPROPERTY(EditAnywhere)
	FString OptionalDisplayText;
};


/**
 * Extra settings specific to your game, meant to contain useful gameplay debug settings
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Gameplay Debug Settings"))
class LYRAGAME_API UMyGameplayDebugSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/** Gameplay tags to add loosely to the player if the settings are on. Default is off
	*/
	UPROPERTY(config, EditAnywhere, Category = Player, meta=(Categories="Player,Loose tags", TitleProperty = "GameplayTag"))
	TArray<FDebugTagDisplay> DebugGameplayTags;
};
