#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemEntryWidget.generated.h"

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, SlotIndex);
 // 拖拽委托
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDragStarted, int32, SlotIndex, UItemEntryWidget*, Widget);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemDropped, int32, TargetSlotIndex, UDragDropOperation*, Operation);

UCLASS()
class DONTLETMEGO_API UItemEntryWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable)
    void SetItemName(const FString& Name);
    
    UFUNCTION(BlueprintCallable)
    void SetItemIcon(UTexture2D* Icon);
    
    UFUNCTION(BlueprintCallable)
    void SetSlotIndex(int32 Index) { SlotIndex = Index; }
    
    UFUNCTION(BlueprintCallable)
    void SetIsEmpty(bool bEmpty) { bIsEmpty = bEmpty; }
    
    UFUNCTION(BlueprintCallable)
    void ClearSlot();

	UFUNCTION(BlueprintCallable)
	void SetItemCount(int32 Count);

	UFUNCTION(BlueprintCallable)
	void SetSelected(bool bSelected);

    // 新增：设置当前物品ID
     UFUNCTION(BlueprintCallable)
    void SetItemID(FName InItemID) { ItemID = InItemID; }
    
    UFUNCTION(BlueprintCallable)
    FName GetItemID() const { return ItemID; }
    // 新增：重置拖拽状态
    UFUNCTION(BlueprintCallable)
    void SetIsDragging(bool bInDragging) { bIsDragging = bInDragging; }
    
    UPROPERTY(BlueprintAssignable)
    FOnItemDragStarted OnItemDragStarted;

    UPROPERTY(BlueprintAssignable)
    FOnItemDropped OnItemDropped;

    UPROPERTY(BlueprintAssignable)
    FOnSlotClicked OnSlotClicked;
    
    UPROPERTY(BlueprintAssignable)
    FOnSlotClicked OnSlotRightClicked;

protected:
        virtual void NativeConstruct() override;

    	virtual FReply NativeOnMouseButtonDown(
        const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent
    ) override;
        virtual FReply NativeOnMouseButtonUp(
        const FGeometry& InGeometry,
        const FPointerEvent& InMouseEvent
    ) override;
            // 拖拽相关
   virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
    virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
   
   


    UPROPERTY()
    bool bIsDragging = false;
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemNameText;
    
    UPROPERTY(meta = (BindWidget))
    class UImage* ItemIconImage;

    UPROPERTY(meta=(BindWidget))
	class UBorder* SelectionBorder;

	UPROPERTY(meta = (BindWidget))
    class UTextBlock* ItemCountText;

    UPROPERTY()
    int32 SlotIndex = -1;
    
    UPROPERTY()
    bool bIsEmpty = true;

        // 新增：记录当前物品ID
    UPROPERTY()
    FName ItemID = NAME_None;
    
    // 新增：记录当前数量
    UPROPERTY()
    int32 ItemCount = 0;
};