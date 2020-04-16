// Fill out your copyright notice in the Description page of Project Settings.

#define printOnScreen(text) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)
#define printFString(text, fstring) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT(text), fstring))



#include "Checkpoint.h"
#include "CustomCar.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	OnActorBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
}

void ACheckpoint::OnOverlapBegin(AActor * OverlappedActor, AActor * OtherActor)
{
	ACustomCar* vehicle = Cast<ACustomCar>(OtherActor);
	if (vehicle->IsValidLowLevel())
	{
		vehicle->UpdateCheckpoint(m_CheckpointId);
		printFString("Other Actor %s: ", *OtherActor->GetName());
	}
}

void ACheckpoint::OnOverlapEnd(AActor * OverlappedActor, AActor * OtherActor)
{

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	if (m_CheckpointId == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("invalid checkpoint id! Insert a instance-unique value between 1-3"))
			return;
	}
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);

}



