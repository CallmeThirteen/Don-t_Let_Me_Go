// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemEntryWidget.h"
#include "Components/TextBlock.h"

void UItemEntryWidget::SetItemName(const FString& Name){
    if(ItemNameText){
        ItemNameText->SetText(FText::FromString(Name));
    }
}
