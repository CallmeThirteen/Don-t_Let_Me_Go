// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusTypes.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTLETMEGO_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	bool bIsMoving=false;


public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FStatusValue Hunger;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FStatusValue Thirst;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FStatusValue Spirit;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FStatusValue Stamina;

	void SetMoving(bool bMoving);

	bool IsMoving()const{
		return bIsMoving;
	}
	
};
