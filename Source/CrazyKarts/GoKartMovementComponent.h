// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.generated.h"

USTRUCT()
struct FGoKartMove
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	float Throttle;
	UPROPERTY()
	float SteeringThrow;
	UPROPERTY()
	float DeltaTime;
	UPROPERTY()
	float Time;

	bool IsValid() const
	{
		return FMath::Abs(Throttle) <= 1 && FMath::Abs(SteeringThrow) <= 1;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRAZYKARTS_API UGoKartMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGoKartMovementComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetVelocity(FVector VelocityToSet);
	void SetThrottle(float ThrottleToSet);
	void SetSteeringThrow(float SteeringThrowToSet);

	FVector GetVelocity() const;
	FGoKartMove GetLastMove() const { return LastMove; };

	void SimulateMove(const FGoKartMove& Move);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	FGoKartMove CreateMove(float DeltaTime);

	FVector Velocity;
	float Throttle;
	float SteeringThrow;
	FGoKartMove LastMove;

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
		
	FVector GetAirResistance();
	FVector GetRollingResistance();
	void UpdateLocationFromVelocity(float DeltaTime);
	void UpdateCarRotation(float DeltaTime, float SteeringThrowForMove);
};
