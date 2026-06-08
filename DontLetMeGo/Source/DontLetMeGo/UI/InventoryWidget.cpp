// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "ItemEntryWidget.h"
#include "Components/ScrollBox.h"

void UInventoryWidget::RefreshInventory(const TArray<FInventorySlot>& Items){
    if(!ItemList){
        return ;
    }
    ItemList->ClearChildren();
    for(const FInventorySlot& InventorySlot:Items){
        UItemEntryWidget* Entry = CreateWidget<UItemEntryWidget>(
            GetWorld(),
            ItemEntryClass
        );
        if(!Entry){
            continue;
        }
        FString DisplayText = FString::Printf(
            TEXT("%s x%d"),
            *InventorySlot.ItemID.ToString(),
            InventorySlot.Count
        );
        Entry->SetItemName(DisplayText);
        ItemList->AddChild(Entry);
    }
}

void UInventoryWidget::SetInventoryComponent(UInventoryComponent* InComponent){
    InventoryComponent = InComponent;
}