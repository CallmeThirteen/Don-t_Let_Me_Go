// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UInventoryComponent::AddItem(
	FName ItemID,
	int32 Count
){
	if(Count<0){
		return false;
	}
	const FItemData* Data = GetItemData(ItemID);
	if(!Data)return false;
	int32 MaxStack = Data->MaxStack;
	for(FInventorySlot& Slot:Slots){
		if(Slot.ItemID!=ItemID){
			continue;
		}
		if(Slot.Count>=MaxStack){
			continue;
		}
		int32 SpaceLeft=MaxStack-Slot.Count;
		if(Count<=SpaceLeft){
			Slot.Count+=Count;
			return true;
		}
		Slot.Count=MaxStack;
		Count -=SpaceLeft;
	}
	while(Count>0){
		FInventorySlot NewSlot;
		NewSlot.ItemID = ItemID;
		if(Count>MaxStack){
			NewSlot.Count=MaxStack;
			Count-=MaxStack;
		}else{
			NewSlot.Count=Count;
			Count=0;
		}
		Slots.Add(NewSlot);
	}
	return true;
}

bool UInventoryComponent::RemoveItem(
	FName ItemID,
	int32 Count
){
	for(int32 i=0;i<Slots.Num();i++){
		if(Slots[i].ItemID == ItemID){
			Slots[i].Count -= Count;
			if(Slots[i].Count<=0){
				Slots.RemoveAt(i);
			}
			return true;
		}
	}
	return false;
}

int32 UInventoryComponent::GetItemCount(FName ItemID) const{
	for(const FInventorySlot& Slot:Slots){
		if(Slot.ItemID == ItemID){
			return Slot.Count;
		}
	}
	return 0;
}

const FItemData* UInventoryComponent::GetItemData(FName ItemID)const{
	if(!ItemDataTable){
		return nullptr;
	}
	return ItemDataTable->FindRow<FItemData>(ItemID,TEXT(""));
}