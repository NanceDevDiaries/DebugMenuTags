// Copyright Epic Games, Inc. All Rights Reserved.

#include "LyraAbilityCost_ItemTagStack.h"

#if !UE_BUILD_SHIPPING
#include "LyraGameplayTags.h"
#include "AbilitySystemComponent.h"
#endif // #if !UE_BUILD_SHIPPING
#include "Equipment/LyraGameplayAbility_FromEquipment.h"
#include "Inventory/LyraInventoryItemInstance.h"
#include "NativeGameplayTags.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(LyraAbilityCost_ItemTagStack)

UE_DEFINE_GAMEPLAY_TAG(TAG_ABILITY_FAIL_COST, "Ability.ActivateFail.Cost");

ULyraAbilityCost_ItemTagStack::ULyraAbilityCost_ItemTagStack()
{
	Quantity.SetValue(1.0f);
	FailureTag = TAG_ABILITY_FAIL_COST;
}

bool ULyraAbilityCost_ItemTagStack::CheckCost(const ULyraGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (const ULyraGameplayAbility_FromEquipment* EquipmentAbility = Cast<const ULyraGameplayAbility_FromEquipment>(Ability))
	{
		if (ULyraInventoryItemInstance* ItemInstance = EquipmentAbility->GetAssociatedItem())
		{
			const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

			const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
			const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

			bool bCanApplyCost = ItemInstance->GetStatTagStackCount(Tag) >= NumStacks;
#if !UE_BUILD_SHIPPING
			bCanApplyCost |= ActorInfo->AbilitySystemComponent->HasMatchingGameplayTag(LyraGameplayTags::Cheat_UnlimitedAmmo);
#endif // #if !UE_BUILD_SHIPPING

			// Inform other abilities why this cost cannot be applied
			if (!bCanApplyCost && OptionalRelevantTags && FailureTag.IsValid())
			{
				OptionalRelevantTags->AddTag(FailureTag);				
			}
			return bCanApplyCost;
		}
	}
	return false;
}

void ULyraAbilityCost_ItemTagStack::ApplyCost(const ULyraGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
#if !UE_BUILD_SHIPPING
	if (ActorInfo->AbilitySystemComponent->HasMatchingGameplayTag(LyraGameplayTags::Cheat_UnlimitedAmmo))
	{
		return; // just don't apply the cost!
	}
#endif // #if !UE_BUILD_SHIPPING
	if (ActorInfo->IsNetAuthority())
	{
		if (const ULyraGameplayAbility_FromEquipment* EquipmentAbility = Cast<const ULyraGameplayAbility_FromEquipment>(Ability))
		{
			if (ULyraInventoryItemInstance* ItemInstance = EquipmentAbility->GetAssociatedItem())
			{
				const int32 AbilityLevel = Ability->GetAbilityLevel(Handle, ActorInfo);

				const float NumStacksReal = Quantity.GetValueAtLevel(AbilityLevel);
				const int32 NumStacks = FMath::TruncToInt(NumStacksReal);

				ItemInstance->RemoveStatTagStack(Tag, NumStacks);
			}
		}
	}
}

