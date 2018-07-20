// Done by Aleksa Raicevic
#include "TankPlayerController.h"
#include "../Public/TankAimingComponent.h"
#include "Public/Tank.h"



#define OUT

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - Begin Play"))
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PlayerTank = Cast<ATank>(InPawn);
		if (!ensure(PlayerTank)) { return; }
		PlayerTank->SetPlayerHealth();
		PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
	}
}

void ATankPlayerController::OnPossess(APawn * PossessedPawn)
{
	Cast<ATank>(PossessedPawn)->SetPlayerHealth();
}

void ATankPlayerController::OnPlayerTankDeath()
{
	StartSpectatingOnly();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // if not possesing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);

	FVector HitLocation; //Location in the 3D world where our Tank is aiming at 

	if (GetSightRayHitLocation(OUT HitLocation))
	{	
		AimingComponent->AimAt(HitLocation);
		
	}
	
}

//Linetrace through crosshair - if it hits landscape return true
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY; 
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); //Seting our Viewport size (it's responsive for diferent screen sizes)
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY); //Screen Location of our Crosshair
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection)) 
	{
		return GetLookVectorHitLocation(LookDirection, OUT HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString()); 	
	}
	else 
	{
		return false;
	}
	
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); //Start Location is where our Camera is 
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange); //Using LookDirection we know where our LineTrace ends

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)) 
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraWorldLocation; // We'll discard this, we only need it in order to call Deproject..

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT CameraWorldLocation, OUT LookDirection);
		
	
}
