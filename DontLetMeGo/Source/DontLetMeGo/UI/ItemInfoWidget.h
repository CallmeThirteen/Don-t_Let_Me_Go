// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Inventory/InventoryTypes.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETMEGO_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemNameText;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HungerValue;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ThirstValue;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SpiritValue;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* StaminaValue;

public:
	UFUNCTION(BlueprintCallable)
	void SetItemInfo(
    const FItemData& Data
	);
};
