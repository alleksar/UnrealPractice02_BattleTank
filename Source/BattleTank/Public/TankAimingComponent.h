// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	
	void AimAt(FVector);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	EFiringState GetFiringState() const;
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int32 GetRoundsLeft()const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;
private:
	UTankAimingComponent();
	void MoveBarrelTowards(FVector);
	bool IsBarrelMoving();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick Type, FActorComponentTickFunction* ThisTickFunction) override;
	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float RealoadTime = 3.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 RoundsLeft = 3;
	double LastFireTime = 0;	
	FVector AimDirection;

		
	
};
