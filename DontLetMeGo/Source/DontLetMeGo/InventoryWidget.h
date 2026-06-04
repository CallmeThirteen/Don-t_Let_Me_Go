// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class UScrollBox;
class UItemEntryWidget;
UCLASS()
class DONTLETMEGO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ItemList;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<UItemEntryWidget> ItemEntryClass;
	
	void RefreshInventory(const TArray<FString>& Items);


};
