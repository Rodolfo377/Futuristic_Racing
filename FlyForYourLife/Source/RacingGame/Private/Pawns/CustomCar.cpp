// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "../../Public/ActorComponents/ACO_SaveGameData.h"
#include "../../Public/ActorComponents/ACO_Hover.h"
#include "../../Public/ActorComponents/ACO_Position.h"
#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "../../Public/Controllers/CarPlayerController.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"
#include "UObject/UObjectGlobals.h"

#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))





// Sets default values
ACustomCar::ACustomCar()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CarEngine = CreateDefaultSubobject<UACO_CarEngine>(TEXT("CarEngine"));
	ensureAlways(CarEngine);
}


int ACustomCar::GetCurrentVelocity()
{
	CurrentVelocity = FVector::DotProduct(GetVelocity(), GetActorForwardVector()) / 10; //Convert into m/s

	if (CurrentVelocity < 0)
		CurrentVelocity *= (-1);

	return CurrentVelocity;
}





void ACustomCar::Init()
{
	ensureAlways(ShipCore);
	ensureAlways(ShipBody);

	/*CarEngine = NewObject<UACO_CarEngine>(this->_getUObject(), UACO_CarEngine::StaticClass(), FName("CarEngine"));
	ensureAlways(CarEngine);*/
	CarEngine->Init();

	CarTimeKeeper = NewObject<UACO_TimeKeeper>(this->_getUObject(), UACO_TimeKeeper::StaticClass(), FName("CarTimeKeeper"));
	ensureAlways(CarTimeKeeper);
	CarTimeKeeper->Init();

	CarHover = NewObject<UACO_Hover>(this->_getUObject(), UACO_Hover::StaticClass(), FName("CarHover"));
	ensureAlways(CarHover);
	CarHover->Init();

	CarPosition = NewObject<UACO_Position>(this->_getUObject(), UACO_Position::StaticClass(), FName("CarPosition"));
	ensureAlways(CarPosition);
	CarPosition->Init();

	PlayerController = GetController<ACarPlayerController>();
	if (PlayerController->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller found!"));
	}
}

void ACustomCar::Update()
{
	CarEngine->Update();
	CarTimeKeeper->Update();
	CarHover->Update();
	CarPosition->Update();
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

int ACustomCar::GetCurrentLap()
{
	ensureAlways(CarTimeKeeper);
	return CarTimeKeeper->GetCurrentLapID();
}




