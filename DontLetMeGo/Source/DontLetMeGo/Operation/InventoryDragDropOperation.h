#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragDropOperation.generated.h"

UCLASS()
class DONTLETMEGO_API UInventoryDragDropOperation : public UDragDropOperation
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
    int32 SourceSlotIndex = -1;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
    UUserWidget* SourceWidget = nullptr;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
    FName DraggedItemID = NAME_None;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DragDrop")
    int32 DraggedCount = 0;

protected:
    // 重写系统底层的拖拽取消回调（修复松手后源格子变透明复原不了的 Bug）
    virtual void DragCancelled_Implementation(const FPointerEvent& PointerEvent) override;
};