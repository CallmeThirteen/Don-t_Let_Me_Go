#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryTypes.generated.h"


USTRUCT(BlueprintType)
struct FItemData:public FTableRowBase{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    FName ItemID;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    int32 MaxStack= 99;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    int32 BuyPrice=0;

    UPROPERTY(EditAnywhere,BlueprintReadOnly)
    int32 SellPrice=0;
};

USTRUCT(BlueprintType)
struct FInventorySlot{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Count=0;
};