// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemEntryWidget.h"
#include "Components/ScrollBox.h"

void UInventoryWidget::RefreshInventory(const TArray<FString>& Items){
    if(!ItemList){
        return ;
    }
    ItemList->ClearChildren();
    for(const FString& ItemName:Items){
        UItemEntryWidget* Entry=CreateWidget<UItemEntryWidget>(
            GetWorld(),
            ItemEntryClass
        );
        if(Entry){
            Entry->SetItemName(ItemName);
            ItemList->AddChild(Entry);
        }
    }
}
