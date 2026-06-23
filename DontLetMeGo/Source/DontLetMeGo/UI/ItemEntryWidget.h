#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemEntryWidget.generated.h"

// ✅ 放在全局命名空间
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotClicked, int32, SlotIndex);

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
};