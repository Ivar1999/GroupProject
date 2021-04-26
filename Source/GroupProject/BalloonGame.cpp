// Fill out your copyright notice in the Description page of Project Settings.


#include "BalloonGame.h"
#include "Kismet/GameplayStatics.h"
ABalloonGame::ABalloonGame()
{


	OnActorBeginOverlap.AddDynamic(this, &ABalloonGame::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ABalloonGame::OnOverlapEnd);

}



void ABalloonGame::BeginPlay()
{
	Super::BeginPlay();



}

void ABalloonGame::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{

	}
}

void ABalloonGame::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{

	}
}
