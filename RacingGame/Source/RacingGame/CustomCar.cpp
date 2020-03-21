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

	//SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	//create dummy root component we can attach things to.
		

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetSimulatePhysics(true);

	RootComponent = OurVisibleComponent;

	//OurVisibleComponent->SetupAttachment(RootComponent);

	/*SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("FloatingCar"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);*/

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("OurSpringArm"));
	SpringArmComponent->SetupAttachment(OurVisibleComponent);
	//SpringArmComponent->AttachTo(RootComponent);
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->bEnableCameraLag = true;	

	//Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurCamera->SetupAttachment(SpringArmComponent);
	OurCamera->SetRelativeLocation(FVector(0, 0, 0));
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

	CarSpeed = FVector::DotProduct(GetVelocity(), GetActorForwardVector());

	{
		Hovering();
		//RootComponent->UpdateChildTransforms();
	}
}

void ACustomCar::Hovering()
{
	FHitResult Hit = RaycastToFloor();
	FVector groundNormal;	
	if (Hit.bBlockingHit)//if hit ground
	{
		float height = Hit.Distance;
		groundNormal = Hit.Normal;
		float forcePercent = 0.0f; // temporary variable for adjusting the force of the thruster for the hovering
		if (height > RaycastReach)
			forcePercent = 0.95f;
		else
			forcePercent = 1.0f;
		FVector upwardsForce = groundNormal * HoverForce * forcePercent;
		UE_LOG(LogTemp, Warning, TEXT("upwards force: (%f, %f, %f)"), upwardsForce.X, upwardsForce.Y, upwardsForce.Z);
		//Apply hover force
		OurVisibleComponent->AddForce(upwardsForce);
		//Apply custom gravity
		FVector downwardsForce = (-1)*groundNormal * HoverGravity * height;
		UE_LOG(LogTemp, Warning, TEXT("downwards force: (%f, %f, %f)"), downwardsForce.X, downwardsForce.Y, downwardsForce.Z);
		OurVisibleComponent->AddForce(downwardsForce);
	}
	else//flying
	{
		UE_LOG(LogTemp, Warning, TEXT("Flying"));
		UE_LOG(LogTemp, Warning, TEXT("fall gravity force: %f)"), -FallGravity);
		OurVisibleComponent->AddForce(FVector(0, 0, -FallGravity));
	}
}

// Called to bind functionality to input
void ACustomCar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("Accelerate", this, &ACustomCar::Accelerate);
		PlayerInputComponent->BindAxis("Steer", this, &ACustomCar::Steer);
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

void ACustomCar::Accelerate(float AxisValue)
{
	//SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	OurVisibleComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	
}

void ACustomCar::Steer(float AxisValue)
{
	FRotator steer = FRotator(0, AxisValue * SteerRate, 0);
	//SphereComponent->AddLocalRotation(steer);
	OurVisibleComponent->AddLocalRotation(steer);
}

