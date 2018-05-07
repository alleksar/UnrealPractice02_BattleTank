// Done by Aleksa Raicevic
#include "../Public/Tank.h"
#include "../Public/TankBarrel.h"
#include "../Public/Projectile.h"
#include "Engine/World.h"


class UProjectileMovementComponent;

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("TANK IS DEAD!"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage to apply is %i --- Damage Amount is %f"), DamageToApply, DamageAmount);

	return DamageToApply;
}
