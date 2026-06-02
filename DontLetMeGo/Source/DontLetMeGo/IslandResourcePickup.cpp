// Copyright Epic Games, Inc. All Rights Reserved.

#include "IslandResourcePickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DontLetMeGoCharacter.h"

AIslandResourcePickup::AIslandResourcePickup()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(RootComponent);
	InteractionSphere->SetSphereRadius(180.0f);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ResourceType = EResourceType::Branch;
	Amount = 1;
}

void AIslandResourcePickup::Collect(ADontLetMeGoCharacter* Collector)
{
	if (!Collector)
	{
		return;
	}

	Collector->AddResource(ResourceType, Amount);
	Destroy();
}

