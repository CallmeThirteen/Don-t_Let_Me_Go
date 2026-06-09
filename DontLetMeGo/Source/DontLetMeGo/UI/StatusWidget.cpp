// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusWidget.h"
#include "../Status/StatusComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"


void UStatusWidget::SetStatusComponent(UStatusComponent* InStatusComponent){
    StatusComponent = InStatusComponent;
}

void UStatusWidget::NativeTick(const FGeometry& MyGeometry,float InDeltaTime){

    Super::NativeTick(MyGeometry,InDeltaTime);
 
    if(!StatusComponent){
        return ;
    }
    if(HungerBar){
        HungerBar->SetPercent(
        StatusComponent->Hunger.CurrentValue /
        StatusComponent->Hunger.MaxValue
    );
    }
    
     if(ThirstBar){
         ThirstBar->SetPercent(
        StatusComponent->Thirst.CurrentValue / 
        StatusComponent->Thirst.MaxValue
    );
    }
   
     if(SpiritBar){
       SpiritBar->SetPercent(
        StatusComponent->Spirit.CurrentValue / 
        StatusComponent->Spirit.MaxValue
    );
    }
    
     if(StaminaBar){
         StaminaBar->SetPercent(
        StatusComponent->Stamina.CurrentValue / 
        StatusComponent->Stamina.MaxValue
    );

    }
   
    if(HungerText){
        HungerText->SetText(FText::AsNumber(FMath::RoundToInt(StatusComponent->Hunger.CurrentValue)));
    }
    if(ThirstText){
        ThirstText->SetText(FText::AsNumber(FMath::RoundToInt(StatusComponent->Thirst.CurrentValue)));
    }
    if(SpiritText){
        SpiritText->SetText(FText::AsNumber(FMath::RoundToInt(StatusComponent->Spirit.CurrentValue)));
    }



}