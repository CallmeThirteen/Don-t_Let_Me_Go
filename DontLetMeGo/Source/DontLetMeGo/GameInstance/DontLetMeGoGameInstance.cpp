// Fill out your copyright notice in the Description page of Project Settings.


#include "DontLetMeGoGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"

void UDontLetMeGoGameInstance::Init(){
    Super::Init();
    FTimerHandle MenuTimer;
    GetTimerManager().SetTimer(MenuTimer, this,&UDontLetMeGoGameInstance::ShowMenuWidget,0.2f,false);

}

void UDontLetMeGoGameInstance::ShowMenuWidget(){
    if(bMenuShow){return ;}
    FString CurrentMap = GetWorld()->GetMapName();
    CurrentMap.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
    if(!CurrentMap.Contains("Menu")&&!CurrentMap.Contains("MainMenu")){
        return;
    }
     if(MenuWidgetClass){
        UUserWidget* Menu=CreateWidget<UUserWidget>(this,MenuWidgetClass);
        if(Menu){
            Menu->AddToViewport();
            
            if(APlayerController* PC=GetWorld()->GetFirstPlayerController()){
                PC->bShowMouseCursor = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(Menu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PC->SetInputMode(InputMode);
        
    }
    }   
    }
}

void UDontLetMeGoGameInstance::StartGame(){
    if(APlayerController* PC=GetWorld()->GetFirstPlayerController()){
        PC->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PC->SetInputMode(InputMode);
    }
    bMenuShow = false;
    UGameplayStatics::OpenLevel(GetWorld(),FName("RoomMap"));
}

void UDontLetMeGoGameInstance::QuitGame(){
    UKismetSystemLibrary::QuitGame(GetWorld(),nullptr,EQuitPreference::Quit,false);
}

void UDontLetMeGoGameInstance::ChangeMap(){
    bIsWake=true;

    UWorld* World=GetWorld();
    if(!World)return;

    if(bIsWake){
        UGameplayStatics::OpenLevel(World,FName("RoomMap"));

    }else{
        UGameplayStatics::OpenLevel(World,FName("IslandMap"));
    }


}


