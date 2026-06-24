// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemInfoWidget.h"
#include "Components/TextBlock.h"

void UItemInfoWidget::SetItemInfo(
    const FItemData& Data)
{
    ItemNameText->SetText(
        Data.DisplayName
    );
    if (Data.RecoverHunger >=0)
    {
        FString HungerStr = FString::Printf(TEXT("+%.0f"), Data.RecoverHunger);
        HungerValue->SetText(FText::FromString(HungerStr));
    }else if(Data.RecoverHunger < 0){
        FString HungerStr = FString::Printf(TEXT("-%.0f"), Data.RecoverHunger);
        HungerValue->SetText(FText::FromString(HungerStr));
    }

    if (Data.RecoverSpirit >=0)
    {
        FString SpiritStr = FString::Printf(TEXT("+%.0f"), Data.RecoverSpirit);
        SpiritValue->SetText(FText::FromString(SpiritStr));
    }else if(Data.RecoverSpirit < 0){
        FString SpiritStr = FString::Printf(TEXT("-%.0f"), Data.RecoverSpirit);
        SpiritValue->SetText(FText::FromString(SpiritStr));
    }

    if (Data.RecoverStamina >=0)
    {
        FString StaminaStr = FString::Printf(TEXT("+%.0f"), Data.RecoverStamina);
        StaminaValue->SetText(FText::FromString(StaminaStr));
    }else if(Data.RecoverStamina < 0){
        FString StaminaStr = FString::Printf(TEXT("-%.0f"), Data.RecoverStamina);
        StaminaValue->SetText(FText::FromString(StaminaStr));
    }

    if (Data.RecoverThirst>=0)
    {
        FString ThirstValueStr = FString::Printf(TEXT("+%.0f"), Data.RecoverThirst);
        ThirstValue->SetText(FText::FromString(ThirstValueStr));
    }else if(Data.RecoverThirst< 0){
        FString ThirstValueStr = FString::Printf(TEXT("-%.0f"), Data.RecoverThirst);
        ThirstValue->SetText(FText::FromString(ThirstValueStr));
    }

    
}