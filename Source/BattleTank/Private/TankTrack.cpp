// Done by Aleksa Raicevic

#include "../Public/TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * MaxTrackDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>( GetOwner()->GetRootComponent()); //We had to cast it into Primitive Component in order to call AddForce
																			
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


