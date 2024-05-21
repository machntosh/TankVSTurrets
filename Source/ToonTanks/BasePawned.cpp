// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawned.h"

// Sets default values
ABasePawned::ABasePawned()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePawned::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawned::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawned::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

