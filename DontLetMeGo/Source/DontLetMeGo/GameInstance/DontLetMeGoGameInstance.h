// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DontLetMeGoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETMEGO_API UDontLetMeGoGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	bool bIsWake=false;
	void ChangeMap();

};
