// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "Actors/Pawns/Characters/NT_Character.h"

// NT
#include "Framework/NT_PlayerController.h"



// Public

// Sets default values
ANT_Character::ANT_Character()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANT_Character::Controller_PawnPossessed()
{
	NetLog(TEXT("Controller confirmed possession."));

	// Do stuff here that you needed to wait for the player controller be aware of you for.
	K2_Controller_PawnPossessed();

	On_PawnReady.Broadcast();
}

void ANT_Character::ServerRPC_Reliable_NotifyClientPawnReady_Implementation()
{
	if (!ServerSide()) return;

	On_PawnReady.Broadcast();
}



// APawn

void ANT_Character::PossessedBy(AController* _newController)
{
	NetLog(TEXT("Pawn possessed."));

	SetOwner(_newController);

	AController* const OldController = Controller;

	Controller = _newController;

	ForceNetUpdate();

	if (Controller->PlayerState != nullptr)
	{
		SetPlayerState(Controller->PlayerState);
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (GetNetMode() != NM_Standalone)
		{
			SetReplicates(true);

			SetAutonomousProxy(true);
		}
	}
	else
	{
		CopyRemoteRoleFrom(GetDefault<APawn>());
	}

	Cast<ANT_PlayerController>(_newController)->On_PawnPossessed.AddDynamic(this, &ANT_Character::Controller_PawnPossessed);

	// dispatch Blueprint event if necessary
	if (OldController != _newController)
	{
		ReceivePossessed(Controller);

		if (UGameInstance* GameInstance = GetGameInstance())
		{
			GameInstance->GetOnPawnControllerChanged().Broadcast(this, Controller);
		}
	}
}

// APawn

// Called to bind functionality to input
void ANT_Character::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}



// AActor

// Called when the game starts or when spawned
void ANT_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANT_Character::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

