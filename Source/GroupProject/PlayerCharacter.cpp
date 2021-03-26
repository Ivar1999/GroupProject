// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "NPC1.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Camera setup
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm comp"));
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera comp"));
	Camera->SetupAttachment(SpringArm);
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//const FVector InitialRotation = GetActorForwardVector();

	//Setting character speed
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	MaxRunSpeed = GetCharacterMovement()->MaxCustomMovementSpeed;
}

void APlayerCharacter::WalkForward(float Value)
{
	const FVector Direction = GetActorForwardVector();

	AddMovementInput(Direction, Value);
	
	//if ((Controller != nullptr) && (Value != 0.0f))
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	// get forward vector
	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	//	AddMovementInput(Direction, Value);
	//}
}

void APlayerCharacter::WalkRight(float Value)
{
	const FVector Direction = GetActorRightVector();
	
	AddMovementInput(Direction, Value);
	//if ((Controller != nullptr) && (Value != 0.0f))
	//{
	//	// find out which way is forward
	//	const FRotator Rotation = Controller->GetControlRotation();
	//	const FRotator YawRotation(0, Rotation.Yaw, 0);

	//	// get forward vector
	//	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	//	AddMovementInput(Direction, Value);
	//}
	
}

void APlayerCharacter::StartRun()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
}

void APlayerCharacter::StopRun()
{
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Walking bindings
	PlayerInputComponent->BindAxis("WalkForward", this, &APlayerCharacter::WalkForward);
	PlayerInputComponent->BindAxis("WalkRight", this, &APlayerCharacter::WalkRight);
	// Character function jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//Interact with NPCs
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APlayerCharacter::InteractWithNPC);
	//
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);
	//Turning
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	
}

void APlayerCharacter::InteractWithNPC()
{
	UE_LOG(LogTemp, Warning, TEXT("Interaction test"));
	TArray<AActor*> Result;

	GetOverlappingActors(Result, ANPC1::StaticClass());
	UINT8 Len = Result.Num();
	for (size_t i = 0; i < Len; i++)
	{
		if (Result[i]->IsA(ANPC1::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Found interaction, %i"), ChatBubbleIndex);
			if (Cast <ANPC1>(Result[i])->ChatBubbleIndex >= 10)
			{
				ChatBubbleIndex = 0;
				Cast <ANPC1>(Result[i])->ChatBubbleIndex = 0;
				UE_LOG(LogTemp, Warning, TEXT("reset val, %i"), ChatBubbleIndex);
			}
			else
			{
				ChatBubbleIndex = Cast <ANPC1>(Result[i])->ChatBubbleIndex++;
				UE_LOG(LogTemp, Warning, TEXT("++, %i"), ChatBubbleIndex);
			}
		}
	}


}