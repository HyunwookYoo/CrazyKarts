// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class CRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float Mass = 1000;

	// The force applied to the car when the throttle is fully down (N).
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;

	// The number of degrees rotated per second at full control throw (degrees/s).	
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10.f;

	// Higher means more drag
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16.f;

	// Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistanceCoefficient = .001f;

	FVector Velocity;
	float Throttle;
	float SteeringThrow;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	void UpdateLocationFromVelocity(float DeltaTime);
	void UpdateCarRotation(float DeltaTime);
	FVector GetAirResistance();
	FVector GetRollingResistance();
};
