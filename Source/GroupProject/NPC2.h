// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "NPC2.generated.h"

UCLASS()
class GROUPPROJECT_API ANPC2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPC2();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* RootBase{ nullptr };
	UPROPERTY(EditAnywhere, Category = "Settings")
		class UCapsuleComponent* CollisionCompClown;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown1;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown2;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown3;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown1New;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown2New;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown3New;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown1Instrument;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown2Instrument;
	UPROPERTY(EditAnywhere, Category = "Settings")
		class USkeletalMeshComponent* Clown3Instrument;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chat Settings")
		int ChatBubbleIndexClown = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Chat Settings")
		bool IsTextVisible = false;

	class UWidgetComponent* ChatWidgetClown = nullptr;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:

};
