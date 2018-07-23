// Done by Aleksa Raicevic

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnPoint();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	AActor* GetSpawnActor() const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;
	UPROPERTY()
	AActor* SpawnActor;

		
	
};
