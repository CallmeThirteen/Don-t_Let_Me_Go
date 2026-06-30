#pragma once

#include "CoreMinimal.h"
#include "../Inventory/InventoryComponent.h"
#include "../Inventory/InventoryTypes.h"
#include "../Operation/InventoryDragDropOperation.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.h"
#include "ItemUseInfoWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UItemEntryWidget;
class UItemInfoWidget;

UCLASS()
class DONTLETMEGO_API UInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY()
    UInventoryComponent* InventoryComponent;

    UFUNCTION(BlueprintCallable)
    void RefreshInventory(const TArray<FInventorySlot>& Items);

    UFUNCTION(BlueprintCallable)
    void CloseItemInfo();
    
    UFUNCTION(BlueprintCallable)
    void CloseItemUseInfo();

    UFUNCTION()
    void OnUseClicked();    
    
    UFUNCTION()
    void OnDropClicked();

    UFUNCTION(BlueprintCallable)
    void SetInventoryComponent(UInventoryComponent* InComponent);

    UFUNCTION(BlueprintImplementableEvent)
    void OnSlotClicked(int32 SlotIndex);

    UFUNCTION(BlueprintImplementableEvent)
    void OnSlotRightClicked(int32 SlotIndex);

    // ✅ 新增：处理拖拽取消（恢复透明度）
    UFUNCTION()
    void HandleDragCancelled(int32 SlotIndex);

protected:
    virtual void NativeConstruct() override;

    virtual FReply NativeOnMouseButtonDown(
        const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent
    ) override;
    
    // ✅ 新增：背景接收Drop（拖到背包外丢弃物品）
    virtual bool NativeOnDrop(
        const FGeometry& InGeometry,
        const FDragDropEvent& InDragDropEvent,
        UDragDropOperation* InOperation
    ) override;

    UItemEntryWidget* CreateSlotWidget(int32 SlotIndex);
    void GetGridPosition(int32 SlotIndex, int32& OutRow, int32& OutColumn) const;

    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* ItemGrid;
    
    UPROPERTY(meta = (BindWidget))
    UUniformGridPanel* HotGrid;
    
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    TSubclassOf<UItemEntryWidget> ItemEntryClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    TSubclassOf<UItemInfoWidget> ItemInfoWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    TSubclassOf<UItemUseInfoWidget> ItemUseInfoWidgetClass;

    UPROPERTY()
    UItemInfoWidget* ItemInfoWidget;

    UPROPERTY()
    UItemUseInfoWidget* ItemUseInfoWidget;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 InventoryGridColumns = 10;
    
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 InventoryMaxSlots = 40;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 HotGridColumns = 1;
    
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 HotMaxSlots = 8;

    UPROPERTY()
    UItemEntryWidget* SelectedWidget = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Inventory")
    int32 SelectedSlot = -1;

    UPROPERTY()
    TArray<UItemEntryWidget*> InventorySlotWidgets;
    
    UPROPERTY()
    TArray<UItemEntryWidget*> HotSlotWidgets;

    UFUNCTION()
    void HandleItemDragStarted(int32 SlotIndex, UItemEntryWidget* Widget);

    // ✅ 修复：参数改为 UDragDropOperation* 匹配委托签名
    UFUNCTION()
    void HandleItemDropped(int32 TargetSlotIndex, UDragDropOperation* Operation);
    
    UFUNCTION()
    void HandleSlotClicked(int32 SlotIndex);

    UFUNCTION()
    void HandleSlotRightClicked(int32 SlotIndex);

    UFUNCTION()
    void HandleInventoryChanged(int32 SlotIndex, FName ItemID);
};