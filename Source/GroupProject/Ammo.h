// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class GROUPPROJECT_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Settings")
		UStaticMeshComponent* AmmoMesh;
	UPROPERTY(VisibleAnywhere, Category = "Settings")
		class UProjectileMovementComponent* AmmoMovementComponent;
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* AmmoCollider;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float AmmoMaxTimeAlive = 2.f;
	float CurrentTimeAlive = 0.f;
	float DamageDone = 10.f;

	UFUNCTION()
		void OnOverlapHit(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	void Target(const FVector& TargetDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:


};
