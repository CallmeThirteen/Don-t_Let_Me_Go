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
	
	bool bMenuShow = false;
protected:
	virtual void Init() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	
public:
	UFUNCTION()
	void ShowMenuWidget();

	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintCallable)
	void QuitGame();

	bool bIsWake=true;

	void ChangetoRoomMap();

	void ChangetoIslandMap();

};
