// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	void InteractWithNPC();

	
	float MaxWalkSpeed{ 0.f };

	float MaxRunSpeed{ 600.f };
	
	float MaxCrouchSpeed{ 150.f };


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



};
