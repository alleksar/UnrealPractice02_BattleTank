// Done by Aleksa Raicevic

#include "../Public/TankBarrel.h"
#include "Engine/World.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	//...
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed*MaxDegreesPerSeconds* GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
