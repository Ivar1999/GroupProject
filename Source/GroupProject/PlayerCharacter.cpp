// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "NPC1.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "RangeWeapon.h"
#include "BalloonGame.h"
#include "Ammo.h"
#include "Instrument.h"

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
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritPitch = true;

	InitialRotation = GetControlRotation();

	TopdownArm = 700.f;
	FPArm = -50.f;
	TopdownLocation = FVector(0.f, 0.f, 0.f);
	TopdownRotation = FRotator(-50, 0.f, 0.f);
	FPLocation = FVector(0.f, 0.f, 50.f);
	FPRotation = FRotator(0.f, 0.f, 0.f);

	SpringArm->TargetArmLength = TopdownArm;
	SpringArm->SetRelativeLocation(TopdownLocation);
	SpringArm->SetRelativeRotation(TopdownRotation);
	
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	


	ShooterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	ShooterMesh->SetupAttachment(RootComponent);
	ShooterMesh->SetHiddenInGame(true);


	GetCharacterMovement()->MaxCustomMovementSpeed = 300.f;

	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = 60.f;

	PickupRange = CreateDefaultSubobject<USphereComponent>(TEXT("PickupRange"));
	PickupRange->SetupAttachment(RootComponent);
	PickupRange->SetSphereRadius(175.f);


	AmmoSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Ammo spawn point comp"));
	AmmoSpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//const FVector InitialRotation = GetActorForwardVector();

	//Setting character speed
	MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	MaxRunSpeed = GetCharacterMovement()->MaxCustomMovementSpeed;
	MaxCrouchSpeed = GetCharacterMovement()->MaxWalkSpeedCrouched;
	
	//FName WeaponSocket = TEXT("WeaponSocket");

	balancing = false;

	// Sets up a weapon on the character, and hides it when the game starts.
	CharWeapon = GetWorld()->SpawnActor<ARangeWeapon>(RangedWeapon);
	if (CharWeapon)
	{
	CharWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	CharWeapon->SetActorHiddenInGame(true);
	}
	
	
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
	if (!InBalance())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
	}
	
}

void APlayerCharacter::StopRun()
{
	if (!InBalance())
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::StartCrouch()
{
	Crouch();		//from CharacterMovement
	GetCharacterMovement()->MaxWalkSpeed = MaxCrouchSpeed;
	//GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 0.6f));		//before we have animations
}

void APlayerCharacter::StopCrouch()
{
	UnCrouch();		//from CharacterMovement
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	//GetMesh()->SetRelativeScale3D(FVector(1.f));				//before we have animations
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
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);
	// crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);	
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);
	
	PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &APlayerCharacter::Interact);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);


}
	
bool APlayerCharacter::InBalance()
{
	return balancing;
}

void APlayerCharacter::Interact()
{
	TArray<AActor*> ActorsInRange;

	PickupRange->GetOverlappingActors(ActorsInRange);
	//UINT8 Items = ActorsInRange.Num();
	UE_LOG(LogTemp, Warning, TEXT("x pressed actors in range:  %d"), ActorsInRange.Num());

	for (int i = 0; i < ActorsInRange.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction test"));
		
		if (ActorsInRange[i]->IsA(ARangeWeapon::StaticClass()))
		{
			ARangeWeapon* ItemCheck = Cast<ARangeWeapon>(ActorsInRange[i]);
			if (ItemCheck && ItemCheck->GetActive() && ItemCheck != CharWeapon)
			{
				UE_LOG(LogTemp, Warning, TEXT("Interaction test2"));
				ItemCheck->Interacted();

				if (CharWeapon)
				{
					CharWeapon->SetActorHiddenInGame(false);
					CanShoot = true;
				}
			}
		}
		if (ActorsInRange[i]->IsA(AInstrument::StaticClass()))
		{
			AInstrument* Instruments = Cast<AInstrument>(ActorsInRange[i]);
			if (Instruments && Instruments->InstrumentGetActive())
			{
				Instruments->InstrumentInteracted();
				UE_LOG(LogTemp, Warning, TEXT("Interaction with instrument"));
				//InstrumentCount++;

			}


		}
		if (ActorsInRange[i]->IsA(ABalloonGame::StaticClass()))
		{
			if (BalloonInteract)
			{
				BalloonInteract = false;
			
			}
			else if(!BalloonInteract)
			{
				BalloonInteract = true;
			}
			GameSwap();
		}
		
	}
}

void APlayerCharacter::GameSwap()
{
	if (BalloonInteract)
	{
		InitialRotation = GetActorRotation();
		//GetControlRotation()
		SpringArm->TargetArmLength = FPArm;
		SpringArm->SetRelativeLocation(FPLocation);
		SpringArm->SetRelativeRotation(FPRotation);
		SpringArm->bInheritYaw = true;
		SpringArm->bInheritPitch = true;
		ShooterMesh->SetHiddenInGame(false);
		GetMesh()->SetHiddenInGame(true);
		EnableShooter = true;
		bUseControllerRotationPitch = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
	else if (!BalloonInteract)
	{

		SetActorRotation(InitialRotation);
		SpringArm->TargetArmLength = TopdownArm;
		SpringArm->SetRelativeLocation(TopdownLocation);
		SpringArm->SetRelativeRotation(TopdownRotation);
		SpringArm->bInheritYaw = false;
		SpringArm->bInheritPitch = false;
		GetMesh()->SetHiddenInGame(false);
		ShooterMesh->SetHiddenInGame(true);
		EnableShooter = false;
		bUseControllerRotationPitch = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		//GetMesh()->SetRelativeRotation(InitialRotation);


	}

}

void APlayerCharacter::Turn(float value)
{
	if (!EnableShooter)
	{
		AddControllerYawInput(value);
	}
	else if (EnableShooter)
	{
		//limited yaw
		// if controlrotation.yaw > 45 -> setcontrol.yaw 45
		// if control.yaw < -45 -> set.yaw -45
		AddControllerYawInput(value);
		if (GetControlRotation().Yaw < 315.f && GetControlRotation().Yaw > 155.f)
		{
			GetController()->SetControlRotation(FRotator(GetControlRotation().Pitch, 315.f, GetControlRotation().Roll));
		}
		if(GetControlRotation().Yaw > 45.f && GetControlRotation().Yaw < 150.f)
		{
			GetController()->SetControlRotation(FRotator(GetControlRotation().Pitch, 45.f, GetControlRotation().Roll));
		}

	}
}

void APlayerCharacter::LookUp(float value)
{
	if (EnableShooter)
	{
		AddControllerPitchInput(value);
		if (GetControlRotation().Pitch < 340.f && GetControlRotation().Pitch > 200.f)
		{
			GetController()->SetControlRotation(FRotator( 340.f, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
		if (GetControlRotation().Pitch > 30.f && GetControlRotation().Pitch < 100.f)
		{
			GetController()->SetControlRotation(FRotator(30.f, GetControlRotation().Yaw, GetControlRotation().Roll));
		}
	}
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

void APlayerCharacter::Shoot()
{
	if (CanShoot)
	{
	FActorSpawnParameters Param;
	Param.Name = "Ammo";
	Param.Instigator = this;
	Param.Owner = this;
	FVector const SpawnLocation = AmmoSpawnPoint->GetComponentLocation();
	FRotator const AmmoRotation = GetActorForwardVector().Rotation();
	const auto Ammo = GetWorld()->SpawnActor<AAmmo>(AmmoClass, SpawnLocation, AmmoRotation);
	}

}
