// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameSettingRegistry.h"

#include "GameSettingCollection.h"
#include "Player/LyraLocalPlayer.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MyGameSettingRegistry)

void UMyGameSettingRegistry::OnInitialize(ULocalPlayer* InLocalPlayer)
{
	Super::OnInitialize(InLocalPlayer);

#if !UE_BUILD_SHIPPING
	ULyraLocalPlayer* LyraLocalPlayer = Cast<ULyraLocalPlayer>(InLocalPlayer);
	DebugSettings = InitializeDebugSettings(LyraLocalPlayer);
	RegisterSetting(DebugSettings);
#endif // #if !UE_BUILD_SHIPPING
}
