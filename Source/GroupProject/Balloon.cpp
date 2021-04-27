// Fill out your copyright notice in the Description page of Project Settings.


#include "Balloon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABalloon::ABalloon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BalloonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BalloonMesh"));
	BalloonMesh->SetupAttachment(RootComponent);

	BalloonCollider = CreateDefaultSubobject<USphereComponent>(TEXT("BalloonCollider"));
	BalloonCollider->SetupAttachment(RootComponent);
	BalloonCollider->SetSphereRadius(30.f);
	RootComponent = BalloonCollider;


}

// Called when the game starts or when spawned
void ABalloon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABalloon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABalloon::OnHit()
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit Test"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explode, GetTransform(), true);

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());

	Destroy();

}

