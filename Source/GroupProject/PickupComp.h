// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PickupComp.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJECT_API UPickupComp : public USphereComponent
{
	GENERATED_BODY()

	UPickupComp();
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	class USphereComponent* SphereComp;



};
