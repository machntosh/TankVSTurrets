// Copyright Get in Game SAS


#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/PlayerController.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 1300.f;
	ProjectileMovementComponent->InitialSpeed = 1300.f;

	ParticlesTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	ParticlesTrail->SetupAttachment(RootComponent);



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation(), GetActorRotation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Get the owner of the projectile
	AActor* MyOwner = GetOwner();
	//If the owner is null return
	if (MyOwner == nullptr) { Destroy(); return; }

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();
	//Get the damage Type  class
	UClass* DamageTypeClass = UDamageType::StaticClass();

	// If the OtherActor is not null and it's not the projectile itself and it's not the owner of the projectile
	if (OtherActor && OtherActor!=this && OtherActor != MyOwner)
	{
		// Apply damage to the OtherActor using the damage value, instigator, the projectile itself, and the damage type class
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);

	    //Spawn Particles OnHit
		if (HitParticles)
		{
		  UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());

		}
	}
	Destroy();

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
	}
	if (HitCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
	}

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

} 

/*Toolbox OutputLog - USE OnHit() Function*/
//**
// ToolBox OUTPUT LOG
// UE_LOG(LogTemp, Warning, TEXT("OnHit"));
//UE_LOG(LogTemp, Warning, TEXT("Hitcomp : %s"), *HitComp->GetName());
//UE_LOG(LogTemp, Warning, TEXT("OtherActor : %s"), *OtherActor->GetName());
//UE_LOG(LogTemp, Warning, TEXT("OtherComp : %s"), *OtherComp->GetName());