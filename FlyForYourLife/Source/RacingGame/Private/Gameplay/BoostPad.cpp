// Fill out your copyright notice in the Description page of Project Settings.


#include "BoostPad.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABoostPad::ABoostPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoostPadMesh = CreateDefaultSubobject<UStaticMeshComponent>("BoostPadMesh");
	Tags.Add(Tag);
}

// Called when the game starts or when spawned
void ABoostPad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoostPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

