// Done by Aleksa Raicevic

#pragma once

#include "Public/Tank.h"
#include "Engine/World.h"
#include "BattleTank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	ATankPlayerController();
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float) override;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookDirection(FVector2D, FVector &) const;
	bool GetLookVectorHitLocation(FVector, FVector &) const;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5f; //crosshair X coordinate is on the center of the screen
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.3333f; //crosshair Y coordinate is on the 1/3 from the top of the screen
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f; //this is in centimeters (We can line trace up to 10 kilometers)

	
	
};
