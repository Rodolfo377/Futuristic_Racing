// Fill out your copyright notice in the Description page of Project Settings.


#include "ACO_Hover.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UACO_Hover::UACO_Hover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UACO_Hover::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	MyCharacter = (ACharacter*)Owner;
	if (!MyCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is not a character"))
			return;
	}
	SetupInputComponent();
	SetupPhysicsHandle();
	// ...
	
}

// Called every frame
void UACO_Hover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UACO_Hover::SetupInputComponent()
{
	InputComponent = Owner->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAxis("Accelerate", this, &UACO_Hover::Accelerate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("At Object: '%s' InputComponent component missing."), *GetOwner()->GetName());
	}
	
}

void UACO_Hover::SetupPhysicsHandle()
{
	PhysicsHandle = Owner->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("At Object: %s Physics Handle component missing."), *GetOwner()->GetName());

	}
}

void UACO_Hover::Accelerate(float value)
{
	if (value > 0.1f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Accelerate"))
		TArray<UActorComponent*> StaticComps;
		StaticComps = Owner->GetComponentsByTag(UActorComponent::StaticClass(), "Thruster");
		for(UActorComponent* mesh : StaticComps)
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding force"))
			UStaticMeshComponent* meshcomponent = Cast<UStaticMeshComponent>(mesh);
			if (!meshcomponent)
			{
				UE_LOG(LogTemp, Error, TEXT("no mesh component found"));
				return;
			}
			meshcomponent->AddForce(FVector(0, 0, -10000));
		}
		
	}
}

