// Fill out your copyright notice in the Description page of Project Settings.


#include "RangeWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ARangeWeapon::ARangeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootBase = CreateDefaultSubobject<USceneComponent>(TEXT("RootBase"));
	SetRootComponent(RootBase);

	PickupBox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision comp"));
	PickupBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	active = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootBase);
	//RootComponent = WeaponMesh;

}

void ARangeWeapon::Interacted()
{
	active = false;
	SetActorHiddenInGame(true);
}

bool ARangeWeapon::GetActive()
{
	return active;
}

// Called when the game starts or when spawned
void ARangeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

