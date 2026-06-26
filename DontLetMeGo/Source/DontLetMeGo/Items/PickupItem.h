// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "PickupItem.generated.h"

UCLASS()
class DONTLETMEGO_API APickupItem : public AActor
{
    GENERATED_BODY()

public:
    APickupItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName ItemID;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* PickupItemMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool bRespawnable = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float RespawnTime = 5.0f;

    UPROPERTY(BlueprintReadOnly, Category = "Item")
    bool bIsActive = true;

    UPROPERTY(VisibleAnywhere)
    class USphereComponent* InteractionSphere;

    UPROPERTY(VisibleAnywhere, Category = "UI")
    class UWidgetComponent* InteractPromptWidget;

    UFUNCTION(BlueprintCallable, Category = "Item")
    void OnPickedUp();

    UFUNCTION()
    void SetActive(bool bActive);

    UFUNCTION()
    void Respawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnBeginOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    UFUNCTION()
    void OnEndOverlap(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex
    );

private:
    FTimerHandle RespawnTimerHandle;
};