// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public APawnBase
{
	GENERATED_BODY()


public:

	ATank();// A l'origine, le constructeur n'etait pas creer.Il a ete creer a posteriori

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	//Returns the Tank Player Controller
	APlayerController* GetTankPlayerController() const { return TankPlayerController;}

	bool bAlive = true;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene Componenents", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Scene Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category="Movement")
		float Speed=200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 100.f;


	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController;
	
	
};
