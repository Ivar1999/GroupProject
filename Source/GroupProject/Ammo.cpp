// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Balloon.h"
#include "BalloonGame.h"
#include "PlayerCharacter.h"
// Sets default values
AAmmo::AAmmo()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AmmoCollider = CreateDefaultSubobject<USphereComponent>(TEXT("AmmoCollider"));
    RootComponent = AmmoCollider;
    AmmoCollider->SetSphereRadius(20.f);
    AmmoCollider->SetGenerateOverlapEvents(true);

    AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
    AmmoMesh->SetupAttachment(RootComponent);

    AmmoMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Ammo Movement comp"));
    AmmoMovementComponent->SetUpdatedComponent(RootComponent);
    AmmoMovementComponent->InitialSpeed = 500.f;
    AmmoMovementComponent->MaxSpeed = 500.f;
    AmmoMovementComponent->bRotationFollowsVelocity = true;
    //AmmoMovementComponent->bShouldBounce = false;
    //AmmoMovementComponent->Bounciness = 0.f;
    AmmoMovementComponent->ProjectileGravityScale = 0.f;




}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
    Super::BeginPlay();
    AmmoCollider->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::OnOverlapHit);

}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AmmoMaxTimeAlive -= DeltaTime;
    if (AmmoMaxTimeAlive <= 0.f)
    {
        Destroy();
    }
}

void AAmmo::OnOverlapHit(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{


    UE_LOG(LogTemp, Warning, TEXT("OnHit Test ammo"));




    if (OtherActor != this && OtherActor)
    {
        if (OtherActor->IsA(ABalloon::StaticClass()))
        {
            ABalloon* balloon = Cast<ABalloon>(OtherActor);
            balloon->OnHit();

            APlayerController* playercontroller = GetWorld()->GetFirstPlayerController();
            {

            }
            if (playercontroller)
            {
                APlayerCharacter* player = Cast<APlayerCharacter>(playercontroller->GetCharacter());
                player->BalloonCounter++;
            }
            UE_LOG(LogTemp, Warning, TEXT("Found Class Test"));
            //Destroy();
        }
        Destroy();

    }

}

void AAmmo::Target(const FVector& TargetDirection)
{
    AmmoMovementComponent->Velocity = AmmoMovementComponent->MaxSpeed * TargetDirection;
}
