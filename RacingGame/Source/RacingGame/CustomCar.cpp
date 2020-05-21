// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCar.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "ACO_CarEngine.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "ACO_CarCollision.h"
#include "Engine/StaticMeshActor.h"

#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))



// Sets default values
ACustomCar::ACustomCar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CarEngine = CreateDefaultSubobject<UACO_CarEngine>(TEXT("CarEngine"));	
	CarCollisionManager = CreateDefaultSubobject<UACO_CarCollision>(TEXT("CarCollision"));
}

void ACustomCar::UpdateCheckpoint(uint32 checkpointId)
{
	if (Checkpoints.size() == 3)
	{
		if ((Checkpoints[0] == 1) && (Checkpoints[1] == 2) && (Checkpoints[2] == 3))
		{
			CurrentLap++;
		}

		if (Checkpoints[2] != checkpointId)
		{
			Checkpoints[0] = Checkpoints[1];
			Checkpoints[1] = Checkpoints[2];
			Checkpoints[2] = checkpointId;
		}
	}
}

int ACustomCar::GetCurrentVelocity()
{
	CurrentVelocity = FVector::DotProduct(GetVelocity(), GetActorForwardVector()) / 10; //Convert into m/s

	if (CurrentVelocity < 0)
		CurrentVelocity *= (-1);

	return CurrentVelocity;
}



// Called when the game starts or when spawned
void ACustomCar::BeginPlay()
{
	Super::BeginPlay();	
	if (!ShipCore->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipCore is not valid!"));
		return;
	}
	if (!ShipBody->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Error, TEXT("ShipBody is not valid!"));
		return;
	}
	if (ShipBody->bEditableWhenInherited)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship body is editable by default"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ship body is NOT editable by default"))
	}

	CarCollisionManager->ResetPhysXParameters();
}



// Called every frame
void ACustomCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	
}



// Called to bind functionality to input
void ACustomCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent && CarEngine)
	{
		PlayerInputComponent->BindAxis("Accelerate", CarEngine, &UACO_CarEngine::Accelerate);
		PlayerInputComponent->BindAxis("Steer", CarEngine, &UACO_CarEngine::Steer);
		PlayerInputComponent->BindAction("LeftBarrelRoll", IE_Pressed, CarEngine, &UACO_CarEngine::LeftBarrelRoll);
		PlayerInputComponent->BindAction("RightBarrelRoll", IE_Pressed, CarEngine, &UACO_CarEngine::RightBarrelRoll);
		
	}
}

void ACustomCar::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	GLog->Log("On Hit");
	GLog->Log(*OtherActor->GetName());
	
}

void ACustomCar::NotifyHit(UPrimitiveComponent * MyComp, AActor * Other, UPrimitiveComponent * OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	GLog->Log("Notify Hit");
	GLog->Log(*Other->GetName());
	if (Other->ActorHasTag("Wall"))
	{
		TakeWallDamage(1);
	}
}


