// Done by Aleksa Raicevic

#include "../Public/SprungWheel.h"
#include "../Public/SpawnPoint.h"
#include "../Public/TankTrack.h"



UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

/*
void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & HitResult)
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	//Here we need to fix tank moving sideways due to inertion
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // how fast is tank sliding sideways
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector(); //
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //divide by 2 because there are 2 tracks
	TankRoot->AddForce(CorrectionForce);
}*/

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * MaxTrackDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}


TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnChild = SpawnPointChild->GetSpawnActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}


	return ResultArray;
}




