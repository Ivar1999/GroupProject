// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC2.h"
#include "Components/CapsuleComponent.h"
#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlayerCharacter.h"
#include "Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"

// Sets default values
ANPC2::ANPC2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootBase = CreateDefaultSubobject<USceneComponent>(TEXT("RootBase"));
	CollisionCompClown = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision comp"));
	Clown1 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Clown 1"));
	Clown2 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Clown 2"));
	Clown3 = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Clown 3"));
	Clown1New = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("New clown 1"));
	Clown2New = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("New clown 2"));
	Clown3New = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("New clown 3"));
	Clown1Instrument = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Instrument 1"));
	Clown2Instrument = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Instrument 2"));
	Clown3Instrument = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Instrument 3"));

	SetRootComponent(RootBase);

	Clown1->SetupAttachment(CollisionCompClown);
	Clown2->SetupAttachment(CollisionCompClown);
	Clown3->SetupAttachment(CollisionCompClown);
	Clown1New->SetupAttachment(CollisionCompClown);
	Clown2New->SetupAttachment(CollisionCompClown);
	Clown3New->SetupAttachment(CollisionCompClown);
	Clown1Instrument->SetupAttachment(CollisionCompClown);
	Clown2Instrument->SetupAttachment(CollisionCompClown);
	Clown3Instrument->SetupAttachment(CollisionCompClown);

	Clown1->SetHiddenInGame(false);
	Clown2->SetHiddenInGame(false);
	Clown3->SetHiddenInGame(false);
	Clown1New->SetHiddenInGame(true);
	Clown2New->SetHiddenInGame(true);
	Clown3New->SetHiddenInGame(true);
	Clown1Instrument->SetHiddenInGame(true);
	Clown2Instrument->SetHiddenInGame(true);
	Clown3Instrument->SetHiddenInGame(true);



}

void ANPC2::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("debug"));
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
			if (player && !player->instrumentsPickedup)
			{
				ChatBubbleIndexClown = 0;
				IsTextVisible = true;
				if (ChatWidgetClown)
				{
					ChatWidgetClown->SetVisibility(true);
				}
			}
			else if (player && player->instrumentsPickedup)
			{
				ChatBubbleIndexClown = 0;
				Clown1->SetHiddenInGame(true);
				Clown2->SetHiddenInGame(true);
				Clown3->SetHiddenInGame(true);
				Clown1New->SetHiddenInGame(false);
				Clown2New->SetHiddenInGame(false);
				Clown3New->SetHiddenInGame(false);
				Clown1Instrument->SetHiddenInGame(false);
				Clown2Instrument->SetHiddenInGame(false);
				Clown3Instrument->SetHiddenInGame(false);

				if (ChatWidgetClown)
				{
					ChatWidgetClown->SetVisibility(false);
				}
			}
			UE_LOG(LogTemp, Warning, TEXT("debug2"));
		}

	}

}

void ANPC2::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor && (OtherActor != this))
	{
		UE_LOG(LogTemp, Warning, TEXT("no overlap"));
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{

			IsTextVisible = false;
			if (ChatWidgetClown)
			{
				ChatWidgetClown->SetVisibility(false);
			}

			UE_LOG(LogTemp, Warning, TEXT("hide widget"));
		}


	}


}

// Called when the game starts or when spawned
void ANPC2::BeginPlay()
{
	Super::BeginPlay();


	ChatWidgetClown = FindComponentByClass<UWidgetComponent>();

	if (ChatWidgetClown)
	{
		ChatWidgetClown->SetVisibility(false);
	}

	CollisionCompClown->OnComponentBeginOverlap.AddDynamic(this, &ANPC2::OnOverlapBegin);
	CollisionCompClown->OnComponentEndOverlap.AddDynamic(this, &ANPC2::OnOverlapEnd);
	
}

// Called every frame
void ANPC2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



