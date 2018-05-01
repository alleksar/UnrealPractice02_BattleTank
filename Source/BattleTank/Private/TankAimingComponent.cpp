// Done by Aleksa Raicevic
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OUT LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OUT LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		))
	{
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		
	}
	/* CODE TO TEST IF EVERYTHING WORKS AS PLANED
	auto TankName = GetOwner()->GetName();// getsafenormal makes it a unit vector
	UE_LOG(LogTemp, Warning, TEXT("%s Firing at %s"),*TankName, *AimDirection.ToString())
	auto PlayerTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *PlayerTankName, *HitLocation.ToString(), *BarrelLocation.ToString() )
	*/
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}


