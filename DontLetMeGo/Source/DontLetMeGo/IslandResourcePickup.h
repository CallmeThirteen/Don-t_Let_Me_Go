// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ResourceTypes.h"
#include "IslandResourcePickup.generated.h"

class ADontLetMeGoCharacter;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DONTLETMEGO_API AIslandResourcePickup : public AActor
{
	GENERATED_BODY()

public:
	AIslandResourcePickup();

	UFUNCTION(BlueprintCallable, Category = "Resource")
	void Collect(ADontLetMeGoCharacter* Collector);

	UFUNCTION(BlueprintPure, Category = "Resource")
	EResourceType GetResourceType() const { return ResourceType; }

	UFUNCTION(BlueprintPure, Category = "Resource")
	int32 GetAmount() const { return Amount; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* InteractionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource")
	EResourceType ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Resource", meta = (ClampMin = "1"))
	int32 Amount;
};

