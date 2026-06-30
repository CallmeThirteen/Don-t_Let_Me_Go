#include "ItemEntryWidget.h"
#include "../Operation/InventoryDragDropOperation.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanel.h" 
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Input/Reply.h"
#include "InputCoreTypes.h"


void UItemEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
   
}

FReply UItemEntryWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        bIsDragging = false;
        return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
    }
    else if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        OnSlotRightClicked.Broadcast(SlotIndex);
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply UItemEntryWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (!bIsDragging && InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        OnSlotClicked.Broadcast(SlotIndex);
        return FReply::Handled();
    }
    return FReply::Unhandled();
}

// ItemEntryWidget.cpp - NativeOnDragDetected 修改

// NativeOnDragDetected - 修复拖拽视觉
void UItemEntryWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    if (bIsEmpty) return;
    
    bIsDragging = true;
    
   
    
    UInventoryDragDropOperation* DragOp = NewObject<UInventoryDragDropOperation>();
    DragOp->SourceSlotIndex = SlotIndex;
    DragOp->SourceWidget = this;
    DragOp->DraggedItemID = ItemID;
    DragOp->DraggedCount = ItemCount;
    UItemEntryWidget* DragVisual =
    CreateWidget<UItemEntryWidget>(
        GetOwningPlayer(),
        GetClass());

    DragVisual->SetItemName(ItemNameText->GetText().ToString());
    DragVisual->SetItemIcon(nullptr);      // 如果以后有Icon这里填
    DragVisual->SetItemCount(ItemCount);

    DragOp->DefaultDragVisual = DragVisual;
    DragOp->Pivot = EDragPivot::CenterCenter;
    
    OnItemDragStarted.Broadcast(SlotIndex, this);
    OutOperation = DragOp;
}


bool UItemEntryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    
    UInventoryDragDropOperation* DragOp = Cast<UInventoryDragDropOperation>(InOperation);
   if (!DragOp)
{
    return false;
}

if (DragOp->SourceSlotIndex == SlotIndex)
{
    return false;
}

if (bIsDragging)
{
    return false;
}

OnItemDropped.Broadcast(SlotIndex, DragOp);
SetSelected(false);
return true;  
  
}

// NativeOnDragEnter - 增强高亮
void UItemEntryWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    UInventoryDragDropOperation* DragOp =
        Cast<UInventoryDragDropOperation>(InOperation);

    if (!DragOp)
    {
        return;
    }

    SetSelected(true);
}

void UItemEntryWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
      SetSelected(false);
}

void UItemEntryWidget::SetItemName(const FString& Name) {
    if (ItemNameText) {
        ItemNameText->SetText(FText::FromString(Name));
    }
}

void UItemEntryWidget::SetItemCount(int32 Count)
{
       ItemCount = Count; 
    if (!ItemCountText)
    {
        return;
    }

    if (Count >=1)
    {
        ItemCountText->SetText(FText::AsNumber(Count));
        ItemCountText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        ItemCountText->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UItemEntryWidget::SetItemIcon(UTexture2D* Icon) {
    if (ItemIconImage) {
        ItemIconImage->SetBrushFromTexture(Icon);
        ItemIconImage->SetVisibility(Icon ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void UItemEntryWidget::SetSelected(bool bSelected)
{
    if (!SelectionBorder)
    {
        return;
    }

    SelectionBorder->SetVisibility(
        bSelected
        ? ESlateVisibility::Visible
        : ESlateVisibility::Hidden
    );
}

void UItemEntryWidget::ClearSlot()
{
    ItemID = NAME_None;
    ItemCount = 0;

    SetItemName("");
    SetItemIcon(nullptr);
    SetItemCount(0);

    SetSelected(false);

    SetIsDragging(false);
    SetIsEmpty(true);
}