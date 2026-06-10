// Copyright Epic Games, Inc. All Rights Reserved.

#include "DontLetMeGoCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "myCamera/FollowCameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryComponent.h"
#include "Status/StatusComponent.h"
#include "Items/PickupItem.h"
#include "UI/InventoryWidget.h"
#include "UI/StatusWidget.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// ADontLetMeGoCharacter

ADontLetMeGoCharacter::ADontLetMeGoCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADontLetMeGoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	UWorld* World=GetWorld();
		if(World){
			FollowCameraActor = World->SpawnActor<AFollowCameraActor>(AFollowCameraActor::StaticClass(),
		FVector(0.f,0.f,500.f), FRotator::ZeroRotator);
			if(FollowCameraActor){
				if(APlayerController* PC = UGameplayStatics::GetPlayerController(this,0)){
					PC->SetViewTarget(FollowCameraActor);
					UE_LOG(LogTemp,Warning,TEXT("Switched To FollowCameraActor"));
				}
			}
		}

	if(StatusWidgetClass){
		StatusWidget=CreateWidget<UStatusWidget>(
			GetWorld(),
			StatusWidgetClass
		);
		if(StatusWidget){
			StatusWidget->AddToViewport();
			StatusWidget->SetStatusComponent(StatusComponent);
		}
	}	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADontLetMeGoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADontLetMeGoCharacter::Move);
		EnhancedInputComponent->BindAction(
    MoveAction,
    ETriggerEvent::Completed,
    this,
    &ADontLetMeGoCharacter::StopMove
);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADontLetMeGoCharacter::Look);

		//ToggleInventory
		EnhancedInputComponent->BindAction(ToggleInventoryAction,ETriggerEvent::Started, this, &ADontLetMeGoCharacter::ToggleInventory);
		
		//PiskUp
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &ADontLetMeGoCharacter::PickUp);

		//Test
		EnhancedInputComponent->BindAction(FunctionTestAction, ETriggerEvent::Started, this, &ADontLetMeGoCharacter::PrintInventory);
	}

}

void ADontLetMeGoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (StatusComponent)
	{
    	StatusComponent->SetMoving(
        	!MovementVector.IsNearlyZero()
    	);
	}
	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ADontLetMeGoCharacter::StopMove()
{
    if (StatusComponent)
    {
        StatusComponent->SetMoving(false);
    }
}

void ADontLetMeGoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	/*FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}*/
}

void ADontLetMeGoCharacter::ToggleInventory(){
	if(!InventoryWidget){
		if(!InventoryWidgetClass){
			UE_LOG(LogTemp,Warning,TEXT("InventoryWidgetClass is not set!"));
			return ;
		}
		InventoryWidget = CreateWidget<UUserWidget>(
			GetWorld(),
			InventoryWidgetClass
		);
		if(!InventoryWidget){
			UE_LOG(LogTemp,Warning,TEXT("Failed to create InventoryWidget!"));
			return ;
		}
	}

	if(!bInventoryOpen){
		UInventoryWidget* InvWidget = Cast<UInventoryWidget>(InventoryWidget);
		if(InvWidget){
			InvWidget->SetInventoryComponent(InventoryComponent);
			InvWidget->RefreshInventory(InventoryComponent->GetSlots());
		}
		InventoryWidget->AddToViewport();
		if(APlayerController* PC = Cast<APlayerController>(GetController())){
			PC->bShowMouseCursor=true;
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			PC->SetInputMode(InputMode);
		}
		bInventoryOpen = true;
	}
	else{
		InventoryWidget->RemoveFromParent();
		if(APlayerController* PC = Cast<APlayerController>(GetController())){
			PC->bShowMouseCursor=false;
			PC->SetInputMode(FInputModeGameOnly());
		}
		bInventoryOpen = false;
	}
}

void ADontLetMeGoCharacter::PickUp(){

	FVector Start = GetActorLocation();
	FVector End = Start;
	FHitResult Hit;

	bool bHit = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Start,
		End,
		100.f,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		{},
		EDrawDebugTrace::ForDuration,
		Hit,
		true
	);

	if(!bHit){
		return;
	}
	if(bHit){
		AActor* HitActor = Hit.GetActor();
		APickupItem* Item=Cast<APickupItem>(HitActor);
		if(Item){
			InventoryComponent->AddItem(Item->ItemID,1);
			if(GEngine){
				FString PickupInfo=FString::Printf(
					TEXT("Pick UP :%s"),
					*Item->ItemID.ToString()
				);
				GEngine->AddOnScreenDebugMessage(
					-1,
					3.f,
					FColor::Green,
					PickupInfo
				);
			}
			UE_LOG(LogTemp,Warning,TEXT("Pick Up : %s"),*Item->ItemID.ToString());
			Item->Destroy();
		}
	}
	/*//LineTrace
	FVector start = FollowCamera->GetComponentLocation();
	FVector end = start + FollowCamera->GetForwardVector()*500.f;

	FHitResult Hit;
	
	bool bHit=GetWorld()->LineTraceSingleByChannel(
		Hit,
		start,
		end,
		ECC_Visibility
	);

	if(bHit){
		AActor* HitActor = Hit.GetActor();

		APickupItem* Item = Cast<APickupItem>(HitActor);
		if(Item){
			Inventory.Add(Item->ItemName);

			if (GEngine)
        {
            FString Msg = FString::Printf(
                TEXT("Picked up: %s"), 
                *Item->ItemName
            );
            
            GEngine->AddOnScreenDebugMessage(
                -1,           // Key
                3.0f,         // 显示 3 秒
                FColor::Green,
                Msg
            );
        }
			UE_LOG(
				LogTemp,Warning,TEXT("Item Name %s"),
				*Item->ItemName
			);

			
			Item->Destroy();
		}

	}*/

	/**DrawDebugLine(
		GetWorld(),
		start,
		end,
		FColor::Red,
		false,
		2.f,
		0,
		2.f
	);*/
}

void ADontLetMeGoCharacter::PrintInventory(){
	UE_LOG(LogTemp,Warning,TEXT("============"));
	if(GEngine){
		FString InventoryNum=FString::Printf(
			TEXT("Inventory count: %d"),
			InventoryComponent->GetSlots().Num()
		);
		GEngine->AddOnScreenDebugMessage(
			-1,
			3.f,
			FColor::Green,
			InventoryNum
		);
	}
	UE_LOG(
				LogTemp,
				Warning,
				TEXT("Inventpry Count: %d"),
				InventoryComponent->GetSlots().Num()
			);

	
	UE_LOG(LogTemp,Warning,TEXT("============"));
}


