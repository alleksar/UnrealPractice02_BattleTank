// Done by Aleksa Raicevic
#include "../Public/TankAIController.h"
#include "../Public/TankAimingComponent.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledAITank = GetPawn();
	if (!ensure(PlayerTank && ControlledAITank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);
	auto AimComponent = ControlledAITank->FindComponentByClass<UTankAimingComponent>();
	AimComponent->AimAt(PlayerTank->GetActorLocation()); //points barrel and turret at our tank

	if (AimComponent->GetFiringState() == EFiringState::Locked)
	{
		AimComponent->Fire(); //shoot at us when ready and locked
	}
	
}
