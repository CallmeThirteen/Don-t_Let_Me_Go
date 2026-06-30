#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.h"
#include "Engine/DataTable.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnItemUsedDelegate,
    int32,
    SlotIndex,
    FName,
    ItemID
);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
    FOnItemChangedDelegate,
    int32,
    SlotIndex,
    FName,
    ItemID
);

class APickupItem;  

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DONTLETMEGO_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInventoryComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintReadOnly)
    TArray<FInventorySlot> Slots;

    UPROPERTY(EditDefaultsOnly, Category="Inventory")
    UDataTable* ItemDataTable;

    UFUNCTION(BlueprintCallable)
    bool AddItem(FName ItemID, int32 Count);

    UFUNCTION(BlueprintCallable)
    bool UseItemAt(int32 SlotIndex);

    UFUNCTION(BlueprintCallable)
    bool UseItemByID(FName ItemID, int32 Count);

    UFUNCTION(BlueprintPure)
    bool CanUseItem() const;


    UPROPERTY(BlueprintAssignable)
   FOnItemUsedDelegate OnItemUsed;
    UPROPERTY(BlueprintAssignable)
   FOnItemChangedDelegate OnItemChanged;

    UFUNCTION(BlueprintCallable, Category="Inventory")
    void ExecuteItemEffect(const FItemData& ItemData, APawn* User);

    UFUNCTION(BlueprintCallable)
    bool RemoveItemAt(int32 SlotIndex);
    UFUNCTION(BlueprintCallable)
    bool RemoveItem(FName ItemID, int32 Count);

    UFUNCTION(BlueprintCallable)
    bool MoveItemToSlot(int32 FromSlot, int32 ToSlot);
   
    UPROPERTY(EditDefaultsOnly, Category="Inventory")
    float DropDistance = 100.0f;                

    UPROPERTY(EditDefaultsOnly, Category="Inventory")
    float DropHeight = 50.0f;                   

    UPROPERTY(EditDefaultsOnly, Category="Inventory")
    int32 InventoryMaxSlots = 40;

    UPROPERTY(EditDefaultsOnly, Category="Inventory")
    int32 HotMaxSlots = 8;
    
    UFUNCTION(BlueprintCallable)
    bool DropItemAt(int32 SlotIndex);            

    UFUNCTION(BlueprintCallable)
    int32 GetItemCount(FName ItemID) const;

    const FItemData* GetItemData(FName ItemID) const;

    UFUNCTION(BlueprintCallable)
    const TArray<FInventorySlot>& GetSlots() const { return Slots; }
};