// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryTypes.h"
#include "ItemUseInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETMEGO_API UItemUseInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	class UButton* UseButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* DropButton;

 	
public:

	void NativeConstruct() override;

	UFUNCTION()
	void HandleUseClicked();

	UFUNCTION()
	void HandleDropClicked();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseClicked);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDropClicked);
	
	UPROPERTY(BlueprintAssignable)
	FOnUseClicked OnUseClicked;
	
	UPROPERTY(BlueprintAssignable)
	FOnDropClicked OnDropClicked;
};
