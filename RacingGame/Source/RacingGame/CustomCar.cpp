// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCar.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT
// Sets default values
ACustomCar::ACustomCar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	//create dummy root component we can attach things to.
	RootComponent = SphereComponent;	

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
	OurVisibleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("FloatingCar"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("OurSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->CameraLagSpeed = CameraLagSpeed;

	//Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(SpringArmComponent);
	OurCamera->SetRelativeLocation(FVector(-250, 0, 250));
	OurCamera->SetRelativeRotation(FRotator(-45, 0, 0));
}

// Called when the game starts or when spawned
void ACustomCar::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ACustomCar::GetReachLineStart()
{
	FVector PlayerPosition;
	FRotator PlayerRotation;	
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPosition, OUT PlayerRotation);
	PlayerPosition = GetActorLocation();


	return PlayerPosition;
}

FVector ACustomCar::GetReachLineEnd()
{
	FVector PlayerPosition;
	FRotator PlayerRotation;
	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerPosition, OUT PlayerRotation);
	PlayerPosition = GetActorLocation();

	return PlayerPosition - GetActorUpVector()*RaycastReach;
}

// Called every frame
void ACustomCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//handle movement based on moveX and moveY axes
	{
		FHitResult Hit = RaycastToFloor();
		if (Hit.bBlockingHit)
		{
			
			SphereComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()));
			UE_LOG(LogTemp, Warning, TEXT("Adding Force"));
			
		}
		else
		{
			SphereComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()*0.75f));
			UE_LOG(LogTemp, Warning, TEXT("Force Out"));
		}
		FVector NewLocation = GetActorLocation() + (CurrentVelocity*DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ACustomCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveX", this, &ACustomCar::Move_XAxis);
		PlayerInputComponent->BindAxis("MoveY", this, &ACustomCar::Move_YAxis);
	}
}

FHitResult ACustomCar::RaycastToFloor()
{
	//Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, this);

	FVector v1 = GetReachLineStart();
	FVector v2 = GetReachLineEnd();

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		v1,
		v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		TraceParameters
	);

	
	//draw debug line representing raycast
	DrawDebugLine(GetWorld(), v1, v2, FColor::Red, false, 0, 0, 10.0f);

	return Hit;
}

void ACustomCar::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void ACustomCar::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

