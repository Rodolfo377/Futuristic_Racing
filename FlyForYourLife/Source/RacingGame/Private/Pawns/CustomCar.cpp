// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/Pawns/CustomCar.h"
#include "../../Public/ActorComponents/ACO_TimeKeeper.h"
#include "../../Public/ActorComponents/ACO_SaveGameData.h"
#include "../../Public/ActorComponents/ACO_Hover.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Public/ActorComponents/ACO_CarEngine.h"
#include "Engine/Engine.h"
#include "DrawDebugHelpers.h"
#include "../../Public/ActorComponents/ACO_CarCollision.h"
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
	ensureAlways(CarEngine);
	CarCollisionManager = CreateDefaultSubobject<UACO_CarCollision>(TEXT("CarCollision"));
	ensureAlways(CarCollisionManager);
	CarTimeKeeper = CreateDefaultSubobject<UACO_TimeKeeper>(TEXT("TimeKeeper"));
	ensureAlways(CarTimeKeeper);
	CarHover = CreateDefaultSubobject<UACO_Hover>(TEXT("CarHover"));
	ensureAlways(CarHover);
	/*GameSaveComponent = CreateDefaultSubobject<UACO_SaveGameData>(TEXT("SaveData"));
	ensureAlways(GameSaveComponent);*/
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
	ensureAlways(ShipCore);
	ensureAlways(ShipBody);


	CarCollisionManager->ResetPhysXParameters();
	CarHover->SetCenterOfMass();
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

int ACustomCar::GetCurrentLap()
{
	ensureAlways(CarTimeKeeper);
	return CarTimeKeeper->GetCurrentLapID();
}




