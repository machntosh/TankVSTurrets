// Copyright Get in Game SAS


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTanksPlayerController) 
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyedTower =  Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		//substratct 1 from TargetTowers
		TargetTowers--;
		//If TargetTowers has reached 0 : Game OVER !
		if (TargetTowers==0){GameOver(true);}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}


void AToonTanksGameMode::HandleGameStart()
{
	// Initialise TargetTowers
	TargetTowers = GetTargetTowersCount();
	//Get the player's Tank Object
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	//Get the Player's controller object
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		//Disable Player imput
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		//Create a timer delegate to re-enable player input after a delay
		FTimerHandle PlayerEnableTimerHandle;

		//// Create a timer delegate to call the SetPlayerEnabledState function on the player controller with a value of true after a delay
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);

		//Set the timer to call the delegate after a specified delay
		 GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
			 PlayerEnableTimerDelegate,
			 StartDelay,
			 false);
	}
	
}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();

    
}
