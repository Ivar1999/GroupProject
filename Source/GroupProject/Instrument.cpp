// Fill out your copyright notice in the Description page of Project Settings.


#include "Instrument.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AInstrument::AInstrument()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBase = CreateDefaultSubobject<USceneComponent>(TEXT("RootBase"));
	SetRootComponent(RootBase);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision comp"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static mesh comp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
	active = true;

	RootComponent = SphereComp;
	StaticMesh->SetupAttachment(SphereComp);



}

void AInstrument::InstrumentInteracted()
{
	active = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

bool AInstrument::InstrumentGetActive()
{
	return active;
}

// Called when the game starts or when spawned
void AInstrument::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInstrument::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

