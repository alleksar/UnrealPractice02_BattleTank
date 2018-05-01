// Done by Aleksa Raicevic
#include "../Public/TankAIController.h"
#include "../Public/Tank.h"


ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller - Begin Play"))

	ATank *Possesed = GetControlledAITank();
	if (Possesed == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller  - You are not posessing a tank"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller - You are posessing a %s"), *(Possesed->GetName()))
	}

	ATank *PlayerTank = GetPlayerTank();
	if (PlayerTank == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank not found"))
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player tank is %s"), *(PlayerTank->GetName()))
	}
	
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO Move towards player
		AimAtPlayer();
		//TODO Fire if ready
	}
	

}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::AimAtPlayer()
{
	FVector PlayerTankPosition = GetPlayerTank()->GetActorLocation();
	GetControlledAITank()->AimAt(PlayerTankPosition);
}