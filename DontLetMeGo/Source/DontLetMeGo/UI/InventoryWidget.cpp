#include "InventoryWidget.h"
#include "ItemEntryWidget.h"
#include "ItemInfoWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"


void UInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (SlotWidgets.Num() == 0 &&ItemGrid && ItemEntryClass)
    {
        ItemGrid->ClearChildren();
        SlotWidgets.Empty();
        
        for (int32 i = 0; i < MaxSlots; ++i)
        {
            UItemEntryWidget* EntryWidget = CreateSlotWidget(i);
            if (EntryWidget)
            {
                SlotWidgets.Add(EntryWidget);
                EntryWidget->ClearSlot();
                UUniformGridSlot* GridSlot = ItemGrid->AddChildToUniformGrid(EntryWidget);
                if (GridSlot)
                {
                    int32 Row, Column;
                    GetGridPosition(i, Row, Column);
                    GridSlot->SetRow(Row);
                    GridSlot->SetColumn(Column);
                }
            }
        }
    }

    
    if(InventoryComponent){
    RefreshInventory(InventoryComponent->GetSlots());
    }
}

FReply UInventoryWidget::NativeOnMouseButtonDown(
    const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    if(ItemInfoWidget)
{
    ItemInfoWidget->RemoveFromParent();
    
    ItemInfoWidget = nullptr;
}

    return Super::NativeOnMouseButtonDown(
        InGeometry,
        InMouseEvent);
}

void UInventoryWidget::RefreshInventory(const TArray<FInventorySlot>& Items)
{

   
    for (int32 i = 0; i < SlotWidgets.Num(); ++i)
    {
        UItemEntryWidget* EntryWidget = SlotWidgets[i];
        if (!EntryWidget) continue;
        
        if (Items.IsValidIndex(i) && !Items[i].ItemID.IsNone() && Items[i].Count > 0)
        {
            const FInventorySlot& Data = Items[i];
            FString DisplayText = FString::Printf(TEXT("%s"), 
                *Data.ItemID.ToString()
            );
            EntryWidget->SetItemName(DisplayText);
            // Slot->SetItemIcon(GetItemIcon(Data.ItemID)); // 需要你自己实现图标查找
            EntryWidget->SetItemCount(Data.Count);
            EntryWidget->SetSlotIndex(i);
            EntryWidget->SetIsEmpty(false);
            
        }else
        {
            // ✅ 槽位为空时清空显示
            EntryWidget->ClearSlot();
        }
       
    }
}

UItemEntryWidget* UInventoryWidget::CreateSlotWidget(int32 SlotIndex)
{
    if (!ItemEntryClass) return nullptr;
    
    UItemEntryWidget* Entry = CreateWidget<UItemEntryWidget>(this, ItemEntryClass);
    if (Entry)
    {
        Entry->SetSlotIndex(SlotIndex);
        Entry->OnSlotClicked.AddDynamic(this, &UInventoryWidget::HandleSlotClicked);
        Entry->OnSlotRightClicked.AddDynamic(this, &UInventoryWidget::HandleSlotRightClicked);
    }
    return Entry;
}

void UInventoryWidget::GetGridPosition(int32 SlotIndex, int32& OutRow, int32& OutColumn) const
{
    OutRow = SlotIndex / GridColumns;
    OutColumn = SlotIndex % GridColumns;
}

void UInventoryWidget::CloseItemInfo(){
    if(ItemInfoWidget)
    {
        ItemInfoWidget->RemoveFromParent();
        ItemInfoWidget = nullptr;
    }
}
void UInventoryWidget::CloseItemUseInfo(){
    if(ItemUseInfoWidget)
    {
        ItemUseInfoWidget->RemoveFromParent();
        ItemUseInfoWidget = nullptr;
    }
}
void UInventoryWidget::HandleSlotClicked(int32 SlotIndex)
{   
    if (ItemInfoWidget)
    {
    ItemInfoWidget->RemoveFromParent();
    ItemInfoWidget = nullptr;

    }
    CloseItemUseInfo();
    SelectedSlot = SlotIndex;
    SelectedUseSlot = SlotIndex;
    for (int32 i = 0; i < SlotWidgets.Num(); i++)
    {
        if (SlotWidgets[i])
        {
            SlotWidgets[i]->SetSelected(
                i == SelectedSlot
            );
        }
    }
    
    OnSlotClicked(SlotIndex);
    
    if(!InventoryComponent)
    {
        return;
    }

    const TArray<FInventorySlot>& InfoSlots =
        InventoryComponent->GetSlots();

    if(!InfoSlots.IsValidIndex(SlotIndex))
    {
        return;
    }

    const FInventorySlot& InfoSlot = InfoSlots[SlotIndex];
    if(InfoSlot.ItemID.IsNone()||InfoSlot.Count<1){
        
        return;
    }
    

    if(ItemInfoWidgetClass)
    {
        ItemInfoWidget =
            CreateWidget<UItemInfoWidget>(
                this,
                ItemInfoWidgetClass
            );

    }
    const FItemData* InfoData =
        InventoryComponent->GetItemData(
            InfoSlot.ItemID
        );

    if(InfoData && ItemInfoWidget)
    {
        ItemInfoWidget->SetItemInfo(
            *InfoData
        );
        FVector2D MousePos;

            GetOwningPlayer()->GetMousePosition(
                MousePos.X,
                MousePos.Y
            );
            ItemInfoWidget->SetPositionInViewport(
            MousePos
            );    
            ItemInfoWidget->SetVisibility(
                ESlateVisibility::HitTestInvisible
            );
            ItemInfoWidget->AddToViewport();
        
      
    }
    
}

void UInventoryWidget::HandleSlotRightClicked(int32 SlotIndex)
{
    CloseItemInfo();
    CloseItemUseInfo();
    SelectedSlot = SlotIndex;
     SelectedDropSlot = SlotIndex;
     
    for (int32 i = 0; i < SlotWidgets.Num(); i++)
    {
        if (SlotWidgets[i])
        {
            SlotWidgets[i]->SetSelected(
                i == SelectedSlot
            );
        }
    }
    if(!InventoryComponent)
    {
        return;
    }

    const TArray<FInventorySlot>& InfoSlots =
        InventoryComponent->GetSlots();

    if(!InfoSlots.IsValidIndex(SlotIndex))
    {
        return;
    }

    const FInventorySlot& InfoSlot = InfoSlots[SlotIndex];
    if(InfoSlot.ItemID.IsNone()||InfoSlot.Count<1){
        
        return;
    }
    
    if(!ItemUseInfoWidgetClass)return;
    if(ItemUseInfoWidgetClass)
    {
        ItemUseInfoWidget =
            CreateWidget<UItemUseInfoWidget>(
                this,
                ItemUseInfoWidgetClass
            );

    }
    ItemUseInfoWidget->OnUseClicked.AddDynamic(
    this,
    &UInventoryWidget::OnUseClicked
    );
    
    ItemUseInfoWidget->OnDropClicked.AddDynamic(
        this,
        &UInventoryWidget::OnDropClicked
    );

    const FItemData* InfoData =
        InventoryComponent->GetItemData(
            InfoSlot.ItemID
        );

    if(InfoData && ItemUseInfoWidget)
    {
        
        FVector2D MousePos;

            GetOwningPlayer()->GetMousePosition(
                MousePos.X,
                MousePos.Y
            );
            ItemUseInfoWidget->SetPositionInViewport(
            MousePos
            );    
            ItemUseInfoWidget->SetVisibility(
                ESlateVisibility::Visible
            );
            ItemUseInfoWidget->AddToViewport();
        
      
    }
    OnSlotRightClicked(SlotIndex);
}

void UInventoryWidget::OnUseClicked()
{
    if(!InventoryComponent)
    {
        return;
    }

    InventoryComponent->UseItemAt(
       SelectedUseSlot
    );

    CloseItemUseInfo();
}
void UInventoryWidget::OnDropClicked()
{
    if(!InventoryComponent)
    {
        return;
    }

    InventoryComponent->RemoveItemAt(
       SelectedDropSlot
    );

    CloseItemUseInfo();
}

void UInventoryWidget::SetInventoryComponent(UInventoryComponent* InComponent)
{
    if (InventoryComponent)
    {
        InventoryComponent->OnItemUsed.RemoveDynamic(
            this,
            &UInventoryWidget::HandleInventoryChanged
        );
    }

    InventoryComponent = InComponent;

    if (InventoryComponent)
    {
        InventoryComponent->OnItemUsed.AddDynamic(
            this,
            &UInventoryWidget::HandleInventoryChanged
        );

        RefreshInventory(InventoryComponent->GetSlots());
    }
}



void UInventoryWidget::HandleInventoryChanged(
    int32 SlotIndex,
    FName ItemID)
{
    if (InventoryComponent)
    {
        RefreshInventory(
            InventoryComponent->GetSlots()
        );
    }
}