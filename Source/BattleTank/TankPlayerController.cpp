// Done by Aleksa Raicevic
#include "TankPlayerController.h"

#define OUT

ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - Begin Play"))

	ATank *Possesed = GetControlledTank();
	if (Possesed == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - You are not posessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller - You are posessing a %s"), *(Possesed->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; } 

	FVector HitLocation; //Location Where our Tank is aiming at 

	if (GetSightRayHitLocation(OUT HitLocation))
	{	
		GetControlledTank()->AimAt(HitLocation);
		//TODO Make the tank barrel and turret aim at this point
	}
	
}

//Linetrace through crosshair - if it hits landscape return true
bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY; 
	GetViewportSize(OUT ViewportSizeX, OUT ViewportSizeY); //Seting our Viewport size (it's responsive for diferent screen sizes)
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY); //Screen Location of our Crosshair
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, OUT LookDirection)) {
		GetLookVectorHitLocation(LookDirection, OUT HitLocation);
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString()); 
		return true;
	}
	else {
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
		ECollisionChannel::ECC_Visibility)) 
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
