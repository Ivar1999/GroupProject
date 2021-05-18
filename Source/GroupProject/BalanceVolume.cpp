// Fill out your copyright notice in the Description page of Project Settings.

#include "BalanceVolume.h"
#include "PlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
			
			//Player->GetCharacterMovement()->MaxCustomMovementSpeed = 125.f;
			//MaxRunSpeed = Player->GetCharacterMovement()->MaxCustomMovementSpeed;
			Player->balancing = true;
			Player->GetCharacterMovement()->MaxWalkSpeed = MaxBalanceSpeed;


			

		}
	}
}

void ABalanceVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor->IsA(APlayerCharacter::StaticClass()))
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
			
			//Player->GetCharacterMovement()->MaxCustomMovementSpeed = 300.f;

			//MaxRunSpeed = Player->GetCharacterMovement()->MaxCustomMovementSpeed;
			Player->balancing = false;
			Player->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
			
		}
	}
}