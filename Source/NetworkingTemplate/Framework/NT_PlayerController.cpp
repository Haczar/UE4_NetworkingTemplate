// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_PlayerController.h"

// Unreal
#include "GameFramework/PlayerState.h"
#include "Interfaces/NetworkPredictionInterface.h"
#include "GameFramework/PawnMovementComponent.h"

// NT

#include "NT_GameInstance.h"
#include "Actors/Pawns/NT_Pawn.h"



// Public

ANT_PlayerController::ANT_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Protected

void ANT_PlayerController::Local_FrameworkInitialized()
{
	NetLog(TEXT("Received framework initialization."));

	if (IsOwningClient())
	{
		if (ServerSide())
		{
			Server_SetOwningClient_FrameworkInitialized();
		}
		else
		{
			ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient();
		}
	}

	K2_Local_FrameworkInitialized();
}

void ANT_PlayerController::PawnReady()
{
	NetLog(TEXT("Player is ready."));

	// Originally: Super::OnPossess(PawnToPossess);
		ChangeState(NAME_Playing);

		if (bAutoManageActiveCameraTarget)
		{
			AutoManageActiveCameraTarget(GetPawn());

			ResetCameraMode();
		}
	// End of Originally: Super::OnPossess(PawnToPossess);

	// Override this and add your own conditions...
	K2_PawnReady();

	if (ServerSide() && IsOwningClient())
	{
		// The server host doesn't have to wait for the player state to replicate.
		OwningClient_Ready();
	}
}

void ANT_PlayerController::Client_ProcessPlayerState()
{
	if (PlayerState != NULL)
	{
		OwningClient_Ready();
	}
}

// This should ONLY occur if EVERYTHING is set to go brrrrr on the owning client side. NO IFS OR BUTS.
void ANT_PlayerController::OwningClient_Ready()
{
	NetLog(TEXT("Owning Client of controller is ready to play."));

	if (IsOwningClient())
	{
		// Do what you gotta do and go brrrrrrr (BP Side).
		K2_OwningClient_Ready();

		// Not sure if I should do it client side..
		//On_OwningClient_Ready.Broadcast();

		ServerRPC_Reliable_NotifyOwningClient_Ready_Implementation();
	}
}

void ANT_PlayerController::ServerRPC_Reliable_NotifyOwningClient_Ready_Implementation()
{
	if (! ServerSide()) return;

	NetLog(TEXT("Owning Client Ready: Notified via RPC."));

	On_OwningClient_Ready.Broadcast();
}

void ANT_PlayerController::Server_SetOwningClient_FrameworkInitialized()
{
	bOwningClient_FrameworkInitialized = true;

	On_OwningClient_PostLogin.Broadcast(this);
}

void ANT_PlayerController::ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient_Implementation()
{
	if (! ServerSide()) return;

	Server_SetOwningClient_FrameworkInitialized();
}



// APlayerController

// Public

bool ANT_PlayerController::CanRestartPlayer()
{
	bool baseCheck = 
		PlayerState && 
		!PlayerState->IsOnlyASpectator() && 
		HasClientLoadedCurrentWorld() && 
		PendingSwapConnection  == NULL
	;

	return baseCheck && bOwningClient_FrameworkInitialized;
}



// AController

void ANT_PlayerController::OnPossess(APawn* _pawnToPossess)
{
	//Super::OnPossess(PawnToPossess);

	if ( _pawnToPossess != NULL && (PlayerState == NULL || !PlayerState->IsOnlyASpectator()) )
	{
		// ====================================================================Originally: Super::OnPossess(PawnToPossess);
			const bool bNewPawn = (GetPawn() != _pawnToPossess);

			if (GetPawn() && bNewPawn)
			{
				UnPossess();
			}

			if (_pawnToPossess->Controller != NULL)
			{
				_pawnToPossess->Controller->UnPossess();
			}

			_pawnToPossess->PossessedBy(this);

			// update rotation to match possessed pawn's rotation
			SetControlRotation( _pawnToPossess->GetActorRotation() );

			SetPawn(_pawnToPossess);

			check(GetPawn() != NULL);

			if (GetPawn() && GetPawn()->PrimaryActorTick.bStartWithTickEnabled)
			{
				GetPawn()->SetActorTickEnabled(true);
			}

			INetworkPredictionInterface* NetworkPredictionInterface = GetPawn() ? Cast<INetworkPredictionInterface>(GetPawn()->GetMovementComponent()) : NULL;

			if (NetworkPredictionInterface)
			{
				NetworkPredictionInterface->ResetPredictionData_Server();
			}

			AcknowledgedPawn = NULL;

			// Local PCs will have the Restart() triggered right away in ClientRestart (via PawnClientRestart()), but the server should call Restart() locally for remote PCs.
			// We're really just trying to avoid calling Restart() multiple times.
			if (!IsLocalPlayerController())
			{
				GetPawn()->Restart();
			}

			ClientRestart(GetPawn());
		//==========================================================End of=================== Originally: Super::OnPossess(PawnToPossess);

		NetLog(TEXT("OnPossess"));

		if (ServerSide())
		{
			Cast<ANT_Pawn>(_pawnToPossess)->On_PawnReady.AddDynamic(this, &ANT_PlayerController::PawnReady);

			On_PawnPossessed.Broadcast();
		}
	}	
}



// AActor

// Public

void ANT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	NetLog(TEXT("BeginPlay"));

	UNT_GameInstance* gInst = GetGameInstance<UNT_GameInstance>();

	gInst->On_Framework_Initialized.AddDynamic(this, &ANT_PlayerController::Local_FrameworkInitialized);

	gInst->Local_NotifyComponentReady(EFramework_ComponentFlag::PlayerController);
}

void ANT_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANT_PlayerController, bOwningClient_FrameworkInitialized);
}

