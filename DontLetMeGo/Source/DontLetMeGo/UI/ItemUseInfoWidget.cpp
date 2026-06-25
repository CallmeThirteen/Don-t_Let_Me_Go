// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemUseInfoWidget.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryTypes.h"
#include "InventoryWidget.h"
#include "Components/Button.h"



void UItemUseInfoWidget::NativeConstruct(){
    Super::NativeConstruct();

    if(UseButton){
        UseButton->OnClicked.AddDynamic(
            this,
            &UItemUseInfoWidget::HandleUseClicked
        );
    }
    if(DropButton){
        DropButton->OnClicked.AddDynamic(
            this,
            &UItemUseInfoWidget::HandleDropClicked
        );
    }
}

void UItemUseInfoWidget::HandleUseClicked()
{
    OnUseClicked.Broadcast();
}

void UItemUseInfoWidget::HandleDropClicked()
{
    OnDropClicked.Broadcast();
}

