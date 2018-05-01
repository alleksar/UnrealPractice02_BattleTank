// Done by Aleksa Raicevic

#include "../Public/TankTurret.h"
#include "Engine/World.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	//...
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed*MaxDegreesPerSeconds* GetWorld()->DeltaTimeSeconds;
	auto RawNewYawRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewYawRotation, 0));
}

