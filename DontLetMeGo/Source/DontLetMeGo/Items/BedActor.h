// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "BedActor.generated.h"



UCLASS()
class DONTLETMEGO_API ABedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABedActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* BedMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* InteractionSphere;

	UPROPERTY(VisibleAnywhere,Category= UI)
	class UWidgetComponent* InteractPromptWidget;
public:	
	// Called every frame
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

	void Sleep(class ADontLetMeGoCharacter* character);
};
