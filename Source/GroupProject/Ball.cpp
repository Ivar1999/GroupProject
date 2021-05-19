// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABall::ABall()
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



void ABall::BallInteracted()
{
	active = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	Destroy();
}

bool ABall::BallGetActive()
{
	return active;
}

void ABall::BallHidden()
{
	active = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	active = false;


}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

