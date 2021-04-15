// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "BalanceVolume.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJECT_API ABalanceVolume : public ATriggerVolume
{
	GENERATED_BODY()

public:
	ABalanceVolume();

protected:
	virtual void BeginPlay() override;

private:

	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

};
