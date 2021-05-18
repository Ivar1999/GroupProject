// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "RangeWeapon.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GROUPPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chat Settings")
		int ChatBubbleIndex = 0;


	//Arm+Straw mesh
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ShooterMesh;

	void GameSwap();

	void Turn(float value);
	void LookUp(float value);

	bool BalloonInteract{ false };

	bool EnableShooter{ false };
	bool CanShoot{ false };


	UPROPERTY(EditAnywhere, Category = "Settings")
		USceneComponent* AmmoSpawnPoint;
	UPROPERTY(EditAnywhere, Category = "Ammo")
		TSubclassOf<class AAmmo> AmmoClass;

	void Shoot();

	//int InstrumentCount = 0;

	FRotator InitialRotation;
	void InteractWithNPC();
	float TopdownArm;
	FVector TopdownLocation;
	FVector FPLocation;


	float FPArm;
	FRotator TopdownRotation;
	FRotator FPRotation;

	bool InBalance();
	bool balancing;

	float MaxWalkSpeed{ 150.f };

	float MaxRunSpeed{ 300.f };
	
	float MaxCrouchSpeed{ 50.f };

	float MaxBalanceSpeed{ 140.f };

	//RangeWeapon
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
		TSubclassOf<class ARangeWeapon> RangedWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class ARangeWeapon* CharWeapon{ nullptr };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Input functions
	void WalkForward(float Value);
	void WalkRight(float Value);

	void StartRun();
	void StopRun();

	void StartCrouch();
	void StopCrouch();

	//FVector InitialRotation;

	//Setting up camera
	UPROPERTY(EditAnywhere, Category = "Settings")
		USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(EditAnywhere, Category = "Settings")
		UCameraComponent* Camera = nullptr;

	void Interact();

	UPROPERTY(EditAnywhere, Category = "Pickup", meta = (AllowPrivateAccess = true))
		USphereComponent* PickupRange;

	

};
