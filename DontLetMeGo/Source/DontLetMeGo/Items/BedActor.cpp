// Fill out your copyright notice in the Description page of Project Settings.


#include "BedActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "../DontLetMeGoCharacter.h"

// Sets default values
ABedActor::ABedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BedMesh = CreateDefaultSubobject<UStaticMeshComponent>(
		TEXT("BedMesh")
	);
	RootComponent = BedMesh;
	InteractionSphere=CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(BedMesh);
	InteractionSphere->SetSphereRadius(200.f);
	
	InteractPromptWidget=CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractPrompt"));
	InteractPromptWidget->SetupAttachment(RootComponent);
	InteractPromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
	InteractPromptWidget->SetDrawSize(FVector2D(200,50));
	InteractPromptWidget->SetVisibility(false);


	InteractionSphere->OnComponentBeginOverlap.
	AddDynamic(
   	 this,
   	 &ABedActor::OnBeginOverlap
	);

	InteractionSphere->OnComponentEndOverlap.
	AddDynamic(
    	this,
  	  &ABedActor::OnEndOverlap
	);


	

}

// Called when the game starts or when spawned
void ABedActor::BeginPlay()
{
	Super::BeginPlay();
}
	


// Called every frame
void ABedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABedActor::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
	InteractPromptWidget->SetVisibility(true);
    if(GEngine){
		FString BedInfo=FString::Printf(TEXT("Sleep!"));
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Yellow,
			BedInfo	
		);
	}
}
void ABedActor::OnEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex
)
{	
	InteractPromptWidget->SetVisibility(false);
    if(GEngine){
		FString BedInfo=FString::Printf(TEXT("Wake Up!"));
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.f,
			FColor::Yellow,
			BedInfo	
		);
	}
}