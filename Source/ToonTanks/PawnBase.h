// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();

	void HandleDestruction();

protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category="Scene Components", meta=(AllowPrivateAccess="true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;

	 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
		 USceneComponent* ProjectileSpawnPoint;

	 UPROPERTY(EditDefaultsOnly,Category="Combat")
	 TSubclassOf<class AProjectile>ProjectileClass;

	 UPROPERTY(EditAnywhere,Category="Combat")
	 class UParticleSystem* ExplosionParticle;

	 UPROPERTY(EditAnywhere, Category="Combat")
	 class USoundBase* DeathSound;

	 UPROPERTY(EditAnywhere, Category = "Combat")
		 TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
