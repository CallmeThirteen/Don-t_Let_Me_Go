#include "ItemEntryWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Input/Reply.h"
#include "InputCoreTypes.h"


void UItemEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
   
}

FReply UItemEntryWidget::NativeOnMouseButtonDown(
    const FGeometry& InGeometry,
    const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        OnSlotClicked.Broadcast(SlotIndex);
        return FReply::Handled();
    }

    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        OnSlotRightClicked.Broadcast(SlotIndex);
        return FReply::Handled();
    }


    return Super::NativeOnMouseButtonDown(
        InGeometry,
        InMouseEvent);
    return Super::NativeOnMouseButtonDown(
        InGeometry,
        InMouseEvent);
}

void UItemEntryWidget::SetItemName(const FString& Name) {
    if (ItemNameText) {
        ItemNameText->SetText(FText::FromString(Name));
    }
}

void UItemEntryWidget::SetItemCount(int32 Count)
{
      
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
        ItemIconImage->SetVisibility(Icon ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
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
    SetItemName("");
    SetItemIcon(nullptr);
    SetItemCount(0);
    SetSelected(false);

}