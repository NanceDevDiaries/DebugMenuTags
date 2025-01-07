// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraGameSettingRegistry.h"
#include "MyGameSettingRegistry.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UMyGameSettingRegistry : public ULyraGameSettingRegistry
{
	GENERATED_BODY()

protected:
	virtual void OnInitialize(ULocalPlayer* InLocalPlayer) override;

#if !UE_BUILD_SHIPPING
	UGameSettingCollection* InitializeDebugSettings(ULyraLocalPlayer* InLocalPlayer);
#endif // #if !UE_BUILD_SHIPPING

	// Implement debug for adding loosely added gameplay tags
	UPROPERTY()
	TObjectPtr<UGameSettingCollection> DebugSettings;

};
