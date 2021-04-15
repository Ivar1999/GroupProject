// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetTrigger.h"
#include "Kismet/GameplayStatics.h"
AResetTrigger::AResetTrigger()
{


	OnActorBeginOverlap.AddDynamic(this, &AResetTrigger::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AResetTrigger::OnOverlapEnd);

}



void AResetTrigger::BeginPlay()
{
	Super::BeginPlay();

	

}

void AResetTrigger::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor !=this))
	{
		RestartingLevel();
	}
}

void AResetTrigger::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		
	}
}
void AResetTrigger::RestartingLevel()
{
	UGameplayStatics::OpenLevel(this, *GetWorld()->GetName(), false);
}