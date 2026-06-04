// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemEntryWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class DONTLETMEGO_API UItemEntryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNameText;

	void SetItemName(const FString& Name);
};
