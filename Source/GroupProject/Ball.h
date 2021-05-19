// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class GROUPPROJECT_API ABall : public AActor
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ABall();

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootBase{ nullptr };
	UPROPERTY(EditAnywhere, Category = "Settings")
		class UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USphereComponent* SphereComp;

	void BallInteracted();

	bool BallGetActive();

	void BallHidden();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool active;



};
