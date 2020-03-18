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
	OurVisibleComponent->SetSimulatePhysics(true);

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
	//SphereComponent->AddForce(GetActorForwardVector()*(-0.1f)*Acceleration);
}

void ACustomCar::ApplySidewaysFriction()
{
}

void ACustomCar::ApplyCustomGravity()
{
	SphereComponent->AddForce(UpwardsForce*(0.05f)*(-1)*GetActorUpVector()*CustomGravity*OurVisibleComponent->GetMass());
	//OurVisibleComponent->AddForce(UpwardsForce*(0.05f)*(-1)*GetActorUpVector()*CustomGravity*OurVisibleComponent->GetMass());
	UE_LOG(LogTemp, Warning, TEXT("Applying custom gravity"));
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
			//OurVisibleComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()));
			//UE_LOG(LogTemp, Warning, TEXT("Adding Force"));
			
		}
		else
		{
			SphereComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()*0.75f));
			//OurVisibleComponent->AddForce(FVector(0, 0, UpwardsForce*OurVisibleComponent->GetMass()*0.75f));
			//UE_LOG(LogTemp, Warning, TEXT("Force Out"));
		}
		ApplyCustomGravity();
		/*FVector NewLocation = GetActorLocation() + (CurrentVelocity*DeltaTime);
		SetActorLocation(NewLocation);*/
		OurVisibleComponent->SetWorldLocation(SphereComponent->GetComponentLocation());
		OurVisibleComponent->SetWorldRotation(SphereComponent->GetComponentRotation());
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
	SphereComponent->AddForce(FVector(GetActorForwardVector()*Acceleration*AxisValue));
}

void ACustomCar::Steer(float AxisValue)
{
	FRotator steer = FRotator(0, AxisValue * SteerRate, 0);
	SphereComponent->AddLocalRotation(steer);
}

