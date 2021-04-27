// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Balloon.generated.h"

UCLASS()
class GROUPPROJECT_API ABalloon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABalloon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnHit();

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* BalloonCollider;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BalloonMesh;

	//Particles when destroyed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "On Destroy")
		class UParticleSystem* Explode{ nullptr };

	//Sound when destroyed
	UPROPERTY(EditAnywhere, Category = "On Destroy")
		class USoundBase* HitSound{ nullptr };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	


};
