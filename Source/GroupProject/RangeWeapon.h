// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RangeWeapon.generated.h"

UCLASS()
class GROUPPROJECT_API ARangeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ARangeWeapon();

	void Interacted();

	bool GetActive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootBase{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Mesh")
		class UStaticMeshComponent* WeaponMesh{ nullptr };
	UPROPERTY(EditAnywhere, Category = "Settings")
		class UCapsuleComponent* PickupBox;

private:
	UPROPERTY()
		bool active;
	
	
};
