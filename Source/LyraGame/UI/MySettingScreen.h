// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LyraSettingScreen.h"
#include "MySettingScreen.generated.h"

/**
 * 
 */
UCLASS()
class LYRAGAME_API UMySettingScreen : public ULyraSettingScreen
{
	GENERATED_BODY()

protected:
	virtual UGameSettingRegistry* CreateRegistry() override;
};
