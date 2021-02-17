// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "Actors/Pawns/NT_Pawn.h"


// NT
#include "Framework/NT_PlayerController.h"



// Public

// Sets default values
ANT_Pawn::ANT_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// APawn

void ANT_Pawn::OnPlayer_PawnPossessed()
{
	UE_LOG(LogTemp, Log, TEXT("NT Pawn: Player confirmed possession."));

	// Do stuff here that you needed to wait for the player controller be aware of you for.
	K2_OnPlayer_PawnPossessed();

	On_PawnReady.Broadcast();
}

void ANT_Pawn::ServerRPC_Reliable_NotifyClientPawnReady_Implementation()
{
	if (! ServerSide()) return;

	On_PawnReady.Broadcast();
}

void ANT_Pawn::PossessedBy(AController* NewController)
{
	UE_LOG(LogTemp, Log, TEXT("NT Pawn: Pawn possessed."));

	SetOwner(NewController);

	AController* const OldController = Controller;

	Controller = NewController;

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

	Cast<ANT_PlayerController>(NewController)->On_PawnPossessed.AddDynamic(this, &ANT_Pawn::OnPlayer_PawnPossessed);

	// dispatch Blueprint event if necessary
	if (OldController != NewController)
	{
		ReceivePossessed(Controller);

		if (UGameInstance* GameInstance = GetGameInstance())
		{
			GameInstance->GetOnPawnControllerChanged().Broadcast(this, Controller);
		}
	}
}

// Called to bind functionality to input
void ANT_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



// AActor

// Called when the game starts or when spawned
void ANT_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANT_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


