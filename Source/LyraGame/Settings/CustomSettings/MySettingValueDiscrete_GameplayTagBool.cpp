// Copyright (c) 2025, NanceDevDiaries

#include "MySettingValueDiscrete_GameplayTagBool.h"

#include "Settings/MySettingsLocal.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(MySettingValueDiscrete_GameplayTagBool)

#define LOCTEXT_NAMESPACE "MySettings"

UMySettingValueDiscrete_GameplayTagBool::UMySettingValueDiscrete_GameplayTagBool(): DefaultValue(0), InitialValue(0)
{
	bReportAnalytics = false;

	OptionValues.Add(TEXT("false"));
	OptionValues.Add(TEXT("true"));

	OptionDisplayTexts.Add(LOCTEXT("OFF", "OFF"));
	OptionDisplayTexts.Add(LOCTEXT("ON", "ON"));
}

void UMySettingValueDiscrete_GameplayTagBool::SetDefaultValue(bool Value)
{
	DefaultValue = Value;
}

void UMySettingValueDiscrete_GameplayTagBool::SetGameplayTagData(const FGameplayTag& GameplayTag, FString OptionalStandInName)
{
	GameplayTagToAddLoosely = GameplayTag;
	OptionalTagStandInName = OptionalStandInName;
	SetDevName(GameplayTag.GetTagName());
	
#if !UE_BUILD_SHIPPING
	SetDisplayName(!OptionalTagStandInName.IsEmpty() ? OptionalTagStandInName : GameplayTag.ToString());
#else
	SetDisplayName(!OptionalTagStandInName.IsEmpty() ?
		FText::FromString(OptionalTagStandInName)
		: FText::FromString(GameplayTag.ToString()));
#endif
	SetDescriptionRichText(LOCTEXT("DebugSetting_Description",
	    "Tags to apply to the local player's ability system component as an infinite gameplay effect if ON. Values persist between play sessions"));
	
	if (GetDefault<UMySettingsLocal>()->GetCustomLooselyAddedGameplayTag().Contains(GameplayTag))
	{
		SetDefaultValue(GetDefault<UMySettingsLocal>()->GetCustomLooselyAddedGameplayTag().Contains(GameplayTag));
	}
	else
	{
		SetDefaultValue(false);
	}
}

void UMySettingValueDiscrete_GameplayTagBool::OnInitialized()
{
	DynamicDetails = FGetGameSettingsDetails::CreateLambda([this](ULocalPlayer&)
	{
		return FText::Format(
			LOCTEXT("DynamicDetails_MySettingValueDiscrete_GameplayTagBool",
			        "Tag '{0}' will be applied to the player's gameplay tag container"),
			FText::FromName(GameplayTagToAddLoosely.GetTagName()));
	});

	Super::OnInitialized();
}

void UMySettingValueDiscrete_GameplayTagBool::StoreInitial()
{
	InitialValue = GetValue();
}

void UMySettingValueDiscrete_GameplayTagBool::ResetToDefault()
{
	SetValue(DefaultValue, EGameSettingChangeReason::ResetToDefault);
}

void UMySettingValueDiscrete_GameplayTagBool::RestoreToInitial()
{
	SetValue(InitialValue, EGameSettingChangeReason::RestoreToInitial);
}

void UMySettingValueDiscrete_GameplayTagBool::SetDiscreteOptionByIndex(int32 Index)
{
	if (ensure(OptionValues.IsValidIndex(Index)))
	{
		SetValue(Index, EGameSettingChangeReason::Change);
	}
}

int32 UMySettingValueDiscrete_GameplayTagBool::GetDiscreteOptionIndex() const
{
	return GetValue();
}

TArray<FText> UMySettingValueDiscrete_GameplayTagBool::GetDiscreteOptions() const
{
	return OptionDisplayTexts;
}

int32 UMySettingValueDiscrete_GameplayTagBool::GetValue() const
{
	return UMySettingsLocal::Get()->GetWantsToAddGameplayTag(GameplayTagToAddLoosely);
}

void UMySettingValueDiscrete_GameplayTagBool::SetValue(int32 NewValue, EGameSettingChangeReason InReason)
{
	bool NewBoolValue = NewValue == 0 ? false : true;
	UMySettingsLocal::Get()->AddOrUpdateLooselyAddedGameplayTag(GameplayTagToAddLoosely, NewBoolValue);

	NotifySettingChanged(InReason);
}

#undef LOCTEXT_NAMESPACE
