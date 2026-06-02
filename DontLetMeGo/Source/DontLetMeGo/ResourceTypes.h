// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ResourceTypes.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Branch UMETA(DisplayName = "Branch"),
	Stone UMETA(DisplayName = "Stone"),
	Grass UMETA(DisplayName = "Grass"),
	Berry UMETA(DisplayName = "Berry"),
	FreshWater UMETA(DisplayName = "Fresh Water")
};

