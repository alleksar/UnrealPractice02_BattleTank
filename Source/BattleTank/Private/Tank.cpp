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
}


