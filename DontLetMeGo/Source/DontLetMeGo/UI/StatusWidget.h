// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Layout/Geometry.h"
#include "../Status/StatusComponent.h"
#include "../Status/StatusTypes.h"
#include "StatusWidget.generated.h"


class UProgressBar;
class UStatusComponent;

UCLASS()
class DONTLETMEGO_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeTick(const FGeometry& MyGeometry,float InDeltaTime)override;

	void SetStatusComponent(UStatusComponent* InStatusComponent);
protected:

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HungerBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* ThirstBar;

	UPROPERTY(meta= (BindWidget))
	UProgressBar* SpiritBar;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* HungerText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThirstText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SpiritText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StaminaText;


	UPROPERTY()
	UStatusComponent* StatusComponent;
	
};
