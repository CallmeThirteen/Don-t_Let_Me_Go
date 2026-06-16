// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Components/Button.h"
#include "../GameInstance/DontLetMeGoGameInstance.h"

void UMenuWidget::NativeConstruct(){
    Super::NativeConstruct();

    if(StartButton){
        StartButton->OnClicked.AddDynamic(
            this,
            &UMenuWidget::OnStartClicked
        );
    }
    if(QuitButton){
        QuitButton->OnClicked.AddDynamic(
            this,
            &UMenuWidget::OnQuitClicked
        );
    }
}

void UMenuWidget::OnStartClicked(){
    if(UDontLetMeGoGameInstance* GI = GetGameInstance<UDontLetMeGoGameInstance>()){
        GI->StartGame();
    }

}

void UMenuWidget::OnQuitClicked(){
    if(UDontLetMeGoGameInstance* GI = GetGameInstance<UDontLetMeGoGameInstance>()){
        GI->QuitGame();
    }
}