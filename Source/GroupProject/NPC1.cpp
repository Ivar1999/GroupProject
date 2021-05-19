// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC1.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerCharacter.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ANPC1::ANPC1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBase = CreateDefaultSubobject<USceneComponent>(TEXT("RootBase"));
	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision comp"));
	SkeletalMesh1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal mesh comp"));
	HappyHerb = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Happy herb skeletal mesh comp"));
	HappyHerbBall = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("happy herb ball Skeletal mesh comp"));
	HerbTrick = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("trick herb Skeletal mesh comp"));
	HerbTrickBall = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("trick herb ball Skeletal mesh comp"));


	SetRootComponent(RootBase);


	SkeletalMesh1->SetupAttachment(CollisionComp);
	HappyHerb->SetupAttachment(CollisionComp);
	HappyHerbBall->SetupAttachment(CollisionComp);
	HerbTrick->SetupAttachment(CollisionComp);
	HerbTrickBall->SetupAttachment(CollisionComp);

	SkeletalMesh1->SetHiddenInGame(false);
	HappyHerb->SetHiddenInGame(true);
	HappyHerbBall->SetHiddenInGame(true);
	HerbTrick->SetHiddenInGame(true);
	HerbTrickBall->SetHiddenInGame(true);

}

// Called when the game starts or when spawned
void ANPC1::BeginPlay()
{
	Super::BeginPlay();



	ChatWidget = FindComponentByClass<UWidgetComponent>();

	if (ChatWidget)
	{
		ChatWidget->SetVisibility(false);
	}

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ANPC1::OnOverlapBegin);
	CollisionComp->OnComponentEndOverlap.AddDynamic(this, &ANPC1::OnOverlapEnd);

}

// Called every frame
void ANPC1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//Shows text bubbles and resets them on overlap
void ANPC1::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("lost 5 health"));
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
			if (player && !player->ballPickedup)
			{
				ChatBubbleIndex = 0;
				IsTextVisible = true;
				if (ChatWidget)
				{
					onOverlap = true;
					ChatWidget->SetVisibility(true);
				}
			}
			else if (player && player->ballPickedup)
			{
				ChatBubbleIndex = 11;
				SkeletalMesh1->SetHiddenInGame(true);
				HappyHerb->SetHiddenInGame(false);
				HappyHerbBall->SetHiddenInGame(false);
				HerbTrick->SetHiddenInGame(true);
				HerbTrickBall->SetHiddenInGame(true);
				if (ChatWidget)
				{
					onOverlap = true;
					ChatWidget->SetVisibility(true);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("lost 5000 health"));
		}

	}
}

//Hides text bubbles on overlap end
void ANPC1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{


	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("no overlap"));
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
			if (player && player->ballPickedup)
			{
				SkeletalMesh1->SetHiddenInGame(true);
				HappyHerb->SetHiddenInGame(true);
				HappyHerbBall->SetHiddenInGame(true);
				HerbTrick->SetHiddenInGame(false);
				HerbTrickBall->SetHiddenInGame(false);

			}
			IsTextVisible = false;
			if (ChatWidget)
			{
				onOverlap = false;
				ChatWidget->SetVisibility(false);

			}

			UE_LOG(LogTemp, Warning, TEXT("hide widget"));
		}


	}


}
