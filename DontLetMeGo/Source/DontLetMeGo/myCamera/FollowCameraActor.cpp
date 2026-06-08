// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCameraActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFollowCameraActor::AFollowCameraActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	RootComponent = Camera;

}

// Called when the game starts or when spawned
void AFollowCameraActor::BeginPlay()
{
	Super::BeginPlay();
	TargetCharacter = UGameplayStatics::GetPlayerCharacter(this,0);
	if(!TargetCharacter){
		return ;
	}
	FVector PlayerLocation = TargetCharacter->GetActorLocation();
	FVector CameraLocation = PlayerLocation+FVector(-600.f,0.f,600.f);
	SetActorLocation(CameraLocation);
	SetActorRotation(
		FRotator(
			0.f,
			0.f,
			0.f
		)
	);
	
}

// Called every frame
void AFollowCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!TargetCharacter){
		return ;
	}
	FVector TargetLocation=TargetCharacter->GetActorLocation()+FVector(
		-600.f,
		0.f,
		600.f);
	//SetActorLocation(TargetLocation);
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(),TargetLocation,DeltaTime,5.f);
	SetActorLocation(NewLocation);
	FRotator LookAtRotation = (TargetCharacter->GetActorLocation()-GetActorLocation()).Rotation();

	SetActorRotation(LookAtRotation);
}

