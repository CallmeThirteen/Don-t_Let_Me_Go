// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class DONTLETMEGO_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;	
public:
	void NativeConstruct() override;
	UFUNCTION()
	void OnStartClicked();
	UFUNCTION()
	void OnQuitClicked();
};
