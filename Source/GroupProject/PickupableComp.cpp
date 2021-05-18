// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableComp.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UPickupableComp::UPickupableComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision comp"));
	
	CollisionComp->SetSphereRadius(300.f);
	// ...
}


// Called when the game starts
void UPickupableComp::BeginPlay()
{
	Super::BeginPlay();



	// ...
	
}


// Called every frame
void UPickupableComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

