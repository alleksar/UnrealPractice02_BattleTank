// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "KismetClasses.h"
#include "Components/SceneComponent.h"
#include "Components/AudioComponent.h"
#include "ParticleDefinitions.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void OnTimerExpire();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	void OnHit(UPrimitiveComponent* HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, FVector NormalImpulse, const FHitResult &HitResult);

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Compontents")
	UAudioComponent* ExplosionSound = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 10;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20;
public:	
	void LaunchProjectile(float);

	
	
};
