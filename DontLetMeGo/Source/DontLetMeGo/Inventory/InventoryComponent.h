// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DONTLETMEGO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



UPROPERTY(BlueprintReadOnly)
TArray<FInventorySlot> Slots;

UPROPERTY(EditDefaultsOnly,Category="Inventory")
UDataTable* ItemDataTable;

UFUNCTION(BlueprintCallable)
bool AddItem(
    FName ItemID,
    int32 Count
);

UFUNCTION(BlueprintCallable)
bool RemoveItem(
    FName ItemID,
    int32 Count
);


UFUNCTION(BlueprintCallable)
int32 GetItemCount(
    FName ItemID
) const;


const FItemData* GetItemData(FName ItemID)const;

const TArray<FInventorySlot>&
GetSlots() const{
    return Slots;
}

		
};
