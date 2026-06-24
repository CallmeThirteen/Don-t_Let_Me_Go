#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<AActor> ItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 MaxStack = 99;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 BuyPrice = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 SellPrice = 0;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float RecoverHunger = 0.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float RecoverThirst = 0.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float RecoverSpirit = 0.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float RecoverStamina = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)  
    bool bUsable = false;

    
};

USTRUCT(BlueprintType)
struct FInventorySlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID=NAME_None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count = 0;


};