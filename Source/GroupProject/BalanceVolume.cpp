// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "BalanceVolume.h"

ABalanceVolume::ABalanceVolume()
{


	OnActorBeginOverlap.AddDynamic(this, &ABalanceVolume::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ABalanceVolume::OnOverlapEnd);

}

void ABalanceVolume::BeginPlay()
{
	Super::BeginPlay();



}
void ABalanceVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		
	}
}

void ABalanceVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{

	}
}