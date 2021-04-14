// Fill out your copyright notice in the Description page of Project Settings.


#include "CircusGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

ACircusGame::ACircusGame()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACircusGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ACircusGame::RestartingLevel()
{
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), false);
}

void ACircusGame::BeginPlay()
{
	Super::BeginPlay();


}
