// Done by Aleksa Raicevic
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/Tank.h"
#include "DrawDebugHelpers.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank)) { return; }
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossesedTankDeath);
	}
}


void ATankAIController::OnPossesedTankDeath()
{
	if (!GetPawn()) { return; }

	GetPawn()->DetachFromControllerPendingDestroy();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledAITank = GetPawn();
	if (!ensure(PlayerTank && ControlledAITank)) { return; }

	if (PlayerTankAtSight())
	{
		MoveToActor(PlayerTank, AcceptanceRadius);
		auto AimComponent = ControlledAITank->FindComponentByClass<UTankAimingComponent>();
		AimComponent->AimAt(PlayerTank->GetActorLocation()); //points barrel and turret at our tank
		if (AimComponent->GetFiringState() == EFiringState::Locked)
		{
			AimComponent->Fire(); //shoot at us when ready, locked and player tank is at sight	
		}
	}
	

	
	
}

bool ATankAIController::PlayerTankAtSight()
{
	auto AIRayCast = Cast<USceneComponent>((GetPawn()->GetComponentsByTag(USceneComponent::StaticClass(), FName("LineTrace")))[0]);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	FHitResult HitResult;
	auto StartLocation = AIRayCast->GetComponentLocation();
	auto EndLocation = PlayerTank->GetActorLocation();
	EndLocation.Z += 200;


	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		//DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(255, 0, 0), false, 0.f, 0.f, 10.f);
		if (HitResult.GetActor() == Cast<AActor>(PlayerTank))
		{
			return true;
		}
		else {
			return false;
		}
		
	}

	return false;
}
