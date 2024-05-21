// Copyright Get in Game SAS

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.f;
	float Health = 0.f;

	//Callback function that responds to the multicast delegate wich is OnTakeAnyDamage
	UFUNCTION()
	void DamageTaken
	(
		AActor* DamagedActor,
		float Damage,
		const UDamageType*DamageType,
		class AController*Instigator,
		AActor* DamageCauser
	);

	class AToonTanksGameMode* ToonTanksGameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
