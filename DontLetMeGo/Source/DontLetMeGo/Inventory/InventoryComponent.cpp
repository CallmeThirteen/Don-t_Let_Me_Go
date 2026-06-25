#include "InventoryComponent.h"
#include "../Status/StatusComponent.h"

UInventoryComponent::UInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Count)
{
    if (Count <= 0) return false;
    
    const FItemData* Data = GetItemData(ItemID);
    if (!Data) return false;
    
    int32 MaxStack = Data->MaxStack;
    
    for (FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID != ItemID) continue;
        if (Slot.Count >= MaxStack) continue;
        
        int32 SpaceLeft = MaxStack - Slot.Count;
        if (Count <= SpaceLeft)
        {
            Slot.Count += Count;
            OnItemUsed.Broadcast(-1, ItemID); 
            return true;
        }
        Slot.Count = MaxStack;
        Count -= SpaceLeft;
    }
    
  
    while (Count > 0)
    {
        FInventorySlot NewSlot;
        NewSlot.ItemID = ItemID;
        NewSlot.Count = FMath::Min(Count, MaxStack);
        Count -= NewSlot.Count;
        Slots.Add(NewSlot);
    }
    
    OnItemUsed.Broadcast(-1, ItemID);
    return true;
}

bool UInventoryComponent::UseItemAt(int32 SlotIndex)
{
    if (!Slots.IsValidIndex(SlotIndex)) return false;
    
    FInventorySlot& Slot = Slots[SlotIndex];
    if (Slot.ItemID.IsNone() || Slot.Count <= 0) return false;
    
    const FItemData* ItemData = GetItemData(Slot.ItemID);
    if (!ItemData) return false;
    if (!ItemData->bUsable) return false;
    
    APawn* UserPawn = Cast<APawn>(GetOwner());
    if (!UserPawn) return false;
    
    ExecuteItemEffect(*ItemData, UserPawn);
    
    Slot.Count--;
    if (Slot.Count <= 0)
    {
        Slot.ItemID = NAME_None;
        Slot.Count = 0;
    }
    
    OnItemUsed.Broadcast(SlotIndex, ItemData->ItemID);
    return true;
}

bool UInventoryComponent::UseItemByID(FName ItemID, int32 Count)
{
    if (ItemID.IsNone() || Count <= 0)
    {
        return false;
    }

    for (int32 UsedCount = 0; UsedCount < Count; ++UsedCount)
    {
        bool bUsedOne = false;

        for (int32 i = 0; i < Slots.Num(); ++i)
        {
            if (Slots[i].ItemID == ItemID && Slots[i].Count > 0)
            {
                bUsedOne = UseItemAt(i);
                break;
            }
        }

        if (!bUsedOne)
        {
            return false;
        }
    }

    return true;
}

bool UInventoryComponent::CanUseItem() const
{
    for (const FInventorySlot& Slot : Slots)
    {
        if (!Slot.ItemID.IsNone() && Slot.Count > 0)
        {
            const FItemData* Data = GetItemData(Slot.ItemID);
            if (Data && Data->bUsable)
            {
                return true;
            }
        }
    }

    return false;
}

void UInventoryComponent::ExecuteItemEffect(const FItemData& ItemData, APawn* User)
{
    // 这里写物品使用的效果
    // 比如：恢复生命值、增加buff等
   
    if (!User)
    {
        return;
    }
    if(!ItemData.bUsable){
        return;
    }
    UStatusComponent* Status =
        User->FindComponentByClass<UStatusComponent>();

    if (!Status)
    {
        return;
    }
    
    Status->AddHunger(
        ItemData.RecoverHunger
    );

    Status->AddThirst(
        ItemData.RecoverThirst
    );

    Status->AddSpirit(
        ItemData.RecoverSpirit
    );

    Status->AddStamina(
        ItemData.RecoverStamina
    );
    
    if (GEngine)
    {
        FString Msg = FString::Printf(TEXT("使用物品: %s"), *ItemData.DisplayName.ToString());
        GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, Msg);
    }
    
    // TODO: 根据 ItemData 执行具体效果
    // 比如：调用 User 上的 HealthComponent 加血
    // 或者：生成一个 Actor 效果
}
bool UInventoryComponent::RemoveItemAt(int32 SlotIndex)
{
    if (!Slots.IsValidIndex(SlotIndex)) return false;
    
    FInventorySlot& Slot = Slots[SlotIndex];
    if (Slot.ItemID.IsNone() || Slot.Count <= 0) return false;
    
    const FItemData* ItemData = GetItemData(Slot.ItemID);
    if (!ItemData) return false;        
    
    Slot.Count--;
    if (Slot.Count <= 0)
    {
        Slot.ItemID = NAME_None;
        Slot.Count = 0;
    }
    
    OnItemUsed.Broadcast(SlotIndex, ItemData->ItemID);
    return true;
}
bool UInventoryComponent::RemoveItem(FName ItemID, int32 Count)
{
    for (int32 i = 0; i < Slots.Num(); i++)
    {
        if (Slots[i].ItemID == ItemID)
        {
            Slots[i].Count -= Count;
            if (Slots[i].Count <= 0)
            {
                Slots.RemoveAt(i);
            }
            OnItemUsed.Broadcast(i, ItemID);
            return true;
        }
    }
    return false;
}

int32 UInventoryComponent::GetItemCount(FName ItemID) const
{
    int32 Total = 0;
    for (const FInventorySlot& Slot : Slots)
    {
        if (Slot.ItemID == ItemID)
        {
            Total += Slot.Count;
        }
    }
    return Total;
}

const FItemData* UInventoryComponent::GetItemData(FName ItemID) const
{
    if (!ItemDataTable) return nullptr;
    return ItemDataTable->FindRow<FItemData>(ItemID, TEXT(""));
}