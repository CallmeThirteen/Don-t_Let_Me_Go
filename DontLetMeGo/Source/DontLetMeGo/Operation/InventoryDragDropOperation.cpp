#include "InventoryDragDropOperation.h"
#include "../UI/ItemEntryWidget.h"

void UInventoryDragDropOperation::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
    Super::DragCancelled_Implementation(PointerEvent);
    
    // 拖拽取消时，强制恢复源格子的视觉状态
    if (SourceWidget)
    {
        if (UItemEntryWidget* SourceEntry = Cast<UItemEntryWidget>(SourceWidget))
        {
            SourceEntry->SetRenderOpacity(1.0f);
            SourceEntry->SetIsDragging(false);
        }
    }
}