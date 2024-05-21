// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values AKA THE CONSTRUCTOR BRO !
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates a new Capsule Component and assign to CapsuleComp variable
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(L"Capsule Collider");
	 RootComponent = CapsuleComp;//Assign the value of CapsulComp to RootComponent in the World
	
	 //Creates a new static mesh component and assign its value to BaseMesh variable
		BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(L"Base Mesh");
		BaseMesh->SetupAttachment(CapsuleComp);//Attaches BaseMesh to CapsuleComp

		TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
		TurretMesh -> SetupAttachment(BaseMesh);

	    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
		ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	
}

void APawnBase::HandleDestruction()
{
	// TODO: Visual and sound FX
	if (ExplosionParticle && DeathSound)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	}

	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh->SetWorldRotation(LookAtRotation);
	
}

void APawnBase::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	// Function to spawn a projectile
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	Projectile->SetOwner(this);
}
