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
	//OurVisibleComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	

	//OurVisibleComponent->SetSimulatePhysics(true);

	SphereComponent->SetSimulatePhysics(true);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("FloatingCar"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("OurSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 300;
	SpringArmComponent->bEnableCameraLag = true;
	

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

void ACustomCar::ApplyFriction()
{
}

void ACustomCar::ApplySidewaysFriction()
{
}

void ACustomCar::ApplyCustomGravity()
{
	//SphereComponent->AddForce(UpwardsForce*(0.05f)*(-1)*GetActorUpVector()*CustomGravity*OurVisibleComponent->GetMass());
	//OurVisibleComponent->AddForce(UpwardsForce*(-1)*GetActorUpVector()*CustomGravity*OurVisibleComponent->GetMass());
	UE_LOG(LogTemp, Warning, TEXT("Applying custom gravity"));
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

		//SphereComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()));
		groundNormal = Hit.Normal;
		float forcePercent = 0.0f; // temporary variable for adjusting the force of the thruster for the hovering
		if (height > 50.0f)
			forcePercent = 0.75f;
		else
			forcePercent = 1.0f;

		//Apply hover force
		SphereComponent->AddForce(groundNormal * HoverForce * forcePercent);
		//Apply custom gravity
		SphereComponent->AddForce((-1)*groundNormal * HoverGravity * height);

	}
	else//flying
	{
		//SphereComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()*0.75f));
		SphereComponent->AddForce(FVector(0, 0, -FallGravity));
		//OurVisibleComponent->AddRelativeRotation();
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
	SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
	
}

void ACustomCar::Steer(float AxisValue)
{
	FRotator steer = FRotator(0, AxisValue * SteerRate, 0);
	//SphereComponent->AddLocalRotation(steer);
	SphereComponent->AddLocalRotation(steer);
}

