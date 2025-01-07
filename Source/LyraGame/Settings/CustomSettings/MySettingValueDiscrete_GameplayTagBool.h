// Copyright (c) 2025, NanceDevDiaries

#pragma once

#include "GameSettingValueDiscrete.h"

#include "MySettingValueDiscrete_GameplayTagBool.generated.h"

enum class EGameSettingChangeReason : uint8;

class UObject;

UCLASS()
class UMySettingValueDiscrete_GameplayTagBool : public UGameSettingValueDiscrete
{
	GENERATED_BODY()
	
public:
	UMySettingValueDiscrete_GameplayTagBool();

	void SetDefaultValue(bool Value);
	
	/** Initialize this setting widget based off the given gameplay tag */
	void SetGameplayTagData(const FGameplayTag& GameplayTag, FString OptionalStandInName = "");
	
	//~UGameSettingValue interface
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;
	//~End of UGameSettingValue interface
	
	//~UGameSettingValueDiscrete interface
	virtual void SetDiscreteOptionByIndex(int32 Index) override;
	virtual int32 GetDiscreteOptionIndex() const override;
	virtual TArray<FText> GetDiscreteOptions() const override;
	//~End of UGameSettingValueDiscrete interface

protected:
	/** ULyraSetting */
	virtual void OnInitialized() override;

	int32 GetValue() const;
	void SetValue(int32 NewValue, EGameSettingChangeReason InReason);
	
	int32 DefaultValue;
	int32 InitialValue;
	
	TArray<FString> OptionValues;
	TArray<FText> OptionDisplayTexts;

	FString OptionalTagStandInName; // Text instead of tag, for better human readability
	FGameplayTag GameplayTagToAddLoosely;
};
