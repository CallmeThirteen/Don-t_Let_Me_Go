#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "StatusTypes.generated.h"

USTRUCT(BlueprintType)
struct FStatusValue{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentValue=100.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxValue=100.f;

    
};