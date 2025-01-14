// Fill out your copyright notice in the Description page of Project Settings.


#include "MySettingScreen.h"

#include "Player/LyraLocalPlayer.h"
#include "Settings/MyGameSettingRegistry.h"

UGameSettingRegistry* UMySettingScreen::CreateRegistry()
{
	UMyGameSettingRegistry* NewRegistry = NewObject<UMyGameSettingRegistry>();

	if (ULyraLocalPlayer* LocalPlayer = CastChecked<ULyraLocalPlayer>(GetOwningLocalPlayer()))
	{
		NewRegistry->Initialize(LocalPlayer);
	}

	return NewRegistry;
}
