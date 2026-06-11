// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../GameInstance/DontLetMeGoGameInstance.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Hunger.CurrentValue -= DeltaTime * 0.1f;
	Thirst.CurrentValue -= DeltaTime * 0.2f;
	Spirit.CurrentValue -= DeltaTime * 0.05f;
	if(Hunger.CurrentValue<=0||Thirst.CurrentValue<=0||Spirit.CurrentValue<=0){
		UDontLetMeGoGameInstance* GI=Cast<UDontLetMeGoGameInstance>(GetWorld()->GetGameInstance());
		if(GI){
			GI->ChangeMap();
		}
	}
	if (bIsMoving)
	{
    	Stamina.CurrentValue -= 8.f * DeltaTime;
	}
	else
	{
    	Stamina.CurrentValue += 5.f * DeltaTime;
	}

Stamina.CurrentValue = FMath::Clamp(
    Stamina.CurrentValue,
    0.f,
    Stamina.MaxValue
);

}

void UStatusComponent::SetMoving(bool bMoving){
	bIsMoving = bMoving;
}

