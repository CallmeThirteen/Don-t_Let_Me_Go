#include "PickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/EngineTypes.h"
#include "../DontLetMeGoCharacter.h"

// Sets default values
APickupItem::APickupItem()
{
    PrimaryActorTick.bCanEverTick = false;

    PickupItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupItemMesh"));
    RootComponent = PickupItemMesh;

    InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
    InteractionSphere->SetupAttachment(PickupItemMesh);
    InteractionSphere->SetSphereRadius(75.f);

    InteractPromptWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractPrompt"));
    InteractPromptWidget->SetupAttachment(PickupItemMesh);
    InteractPromptWidget->SetWidgetSpace(EWidgetSpace::Screen);
    InteractPromptWidget->SetVisibility(false);

    InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OnBeginOverlap);
    InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &APickupItem::OnEndOverlap);
}

void APickupItem::BeginPlay()
{
    Super::BeginPlay();

    if (InteractPromptWidget)
    {
        InteractPromptWidget->InitWidget();
    }

    SetActive(bIsActive);
}

void APickupItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APickupItem::SetActive(bool bActive)
{
    bIsActive = bActive;
    SetActorHiddenInGame(!bActive);
    SetActorEnableCollision(bActive);

    if (InteractPromptWidget)
    {
        InteractPromptWidget->SetVisibility(false);
    }
}

void APickupItem::OnPickedUp()
{
    if (!bIsActive) return;

    if (!bRespawnable)
    {
        Destroy();
        return;
    }

    SetActive(false);

    if (bRespawnable && RespawnTime > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(
            RespawnTimerHandle,
            this,
            &APickupItem::Respawn,
            RespawnTime,
            false
        );
    }
}

void APickupItem::Respawn()
{
    SetActive(true);
}

void APickupItem::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult
)
{
    if (bIsActive && InteractPromptWidget)
    {
        InteractPromptWidget->SetVisibility(true);
    }

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Item!"));
    }
}

void APickupItem::OnEndOverlap(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex
)
{
    if (InteractPromptWidget)
    {
        InteractPromptWidget->SetVisibility(false);
    }
}