// Done by Aleksa Raicevic
#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


class UProjectileMovementComponent;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	if (CurrentHealth == 0)
	{
		CurrentHealth = StartingHealth;
		bIsPlayerTank = false;
	}
	
	UE_LOG(LogTemp,Warning,TEXT("Name of tank created is %s"), *this->GetName())
}

void ATank::SetPlayerHealth()
{
	bIsPlayerTank = true;
	CurrentHealth = StartingHealth * 5;
	UE_LOG(LogTemp, Warning, TEXT("Name of tank which got his health updated is %s and current health is %d"), *this->GetName(), CurrentHealth)
}

bool ATank::PlayerTankAtSight()
{
	auto AIRayCast = Cast<USceneComponent>((this->GetComponentsByTag(USceneComponent::StaticClass(), FName("LineTrace")))[0]);
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
float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}

float ATank::GetHealthPercentage() const
{
	if (bIsPlayerTank)
	{
		return (float)CurrentHealth / (float)(StartingHealth * 5);
	}
	else {
		return (float)CurrentHealth / (float)StartingHealth;
	}
	
}

bool ATank::IsPlayerTank() const
{
	return bIsPlayerTank;
}
