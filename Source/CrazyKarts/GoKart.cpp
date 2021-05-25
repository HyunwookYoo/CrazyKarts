// Fill out your copyright notice in the Description page of Project Settings.


#include "GoKart.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/GameStateBase.h"
#include "GoKartMovementComponent.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// No need to do it because this is already true in Pawn.cpp
	bReplicates = true;

	GoKartMovementComponent = CreateDefaultSubobject<UGoKartMovementComponent>(TEXT("Go Kart Movement Component"));
	GoKartMovementReplicator = CreateDefaultSubobject<UGoKartMovementReplicator>(TEXT("Go Kart Movement Replicator"));
}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		NetUpdateFrequency = 1.f;
	}

	SetReplicateMovement(false);
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
		break;
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
		break;
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
		break;
	case ROLE_Authority:
		return "Authority";
		break;
	default:
		return "ERROR";
		break;
	}
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugString(GetWorld(), FVector(0.f, 0.f, 100.f), GetEnumText(GetLocalRole()), this, FColor::White, DeltaTime);
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AGoKart::MoveRight);
}

void AGoKart::MoveForward(float Axis)
{
	if (GoKartMovementComponent == nullptr) return;

	GoKartMovementComponent->SetThrottle(Axis);
}

void AGoKart::MoveRight(float Axis)
{
	if (GoKartMovementComponent == nullptr) return;

	GoKartMovementComponent->SetSteeringThrow(Axis);
}
