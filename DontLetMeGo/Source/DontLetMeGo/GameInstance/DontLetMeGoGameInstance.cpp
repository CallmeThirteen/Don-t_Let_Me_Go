// Fill out your copyright notice in the Description page of Project Settings.


#include "DontLetMeGoGameInstance.h"
#include "Kismet/GameplayStatics.h"


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


