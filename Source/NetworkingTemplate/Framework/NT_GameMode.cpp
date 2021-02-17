// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_GameMode.h"

// Unreal
#include "GameFramework/GameSession.h"

// NT
#include "NT_GameInstance.h"
#include "NT_PlayerState.h"
#include "NT_PlayerController.h"



// Public

ANT_GameMode::ANT_GameMode()
{
}



// Protected

void ANT_GameMode::Server_OwningClient_PostLogin(ANT_PlayerController* _player)
{
	HandleStartingNewPlayer(_player);
}

void ANT_GameMode::Server_FrameworkInitialized()
{
	NetLog(TEXT("Received framework initialization."));

	bool result = false;

	result = MatchState == MatchState::WaitingToStart;
	result = ReadyToStartMatch_Implementation();   
	// ^^ For some reason I couldn't just call ReadyToStartMatch (override didn't work)

	// Check to see if we should immediately transfer to match start
	if (result)
	{
		StartMatch();
	}

	K2_Server_FrameworkInitialized();
}


// AGameMode

// Protected

// 'Crosses fingers'
bool ANT_GameMode::ReadyToStartMatch_Implementation()
{
	Super::ReadyToEndMatch();

	if (! GetGameInstance<UNT_GameInstance>()->Local_IsFrameworkInitialized()) 
	{
		return false;
	}

	// If bDelayed Start is set, wait for a manual match start
	if (bDelayedStart)
	{
		return false;
	}

	// By default start when we have > 0 players
	if (GetMatchState() == MatchState::WaitingToStart)
	{
		if (NumPlayers + NumBots > 0)
		{
			return true;
		}
	}

	return false;
}



// AGameModeBase

// Protected

void ANT_GameMode::StartPlay()
{
	// Don't call super, this class handles begin play/match start itself

	if (this->MatchState == MatchState::EnteringMap)
	{
		SetMatchState(MatchState::WaitingToStart);
	}

	// Start match is deferred until the framework is considered initialized.

	NetLog(TEXT("StartPlay"));

	UNT_GameInstance* gInst = GetGameInstance<UNT_GameInstance>();

	gInst->On_Framework_Initialized.AddDynamic(this, &ANT_GameMode::Server_FrameworkInitialized);

	gInst->Local_NotifyComponentReady(EFramework_ComponentFlag::GameMode);

	//Super::StartPlay();
}

void ANT_GameMode::PostLogin(APlayerController* NewPlayer)
{
	//Super::PostLogin()

	UWorld* World = GetWorld();

	// update player count
	if (MustSpectate(NewPlayer))
	{
		NumSpectators++;
	}
	else if (World->IsInSeamlessTravel() || NewPlayer->HasClientLoadedCurrentWorld())
	{
		NumPlayers++;
	}
	else
	{
		NumTravellingPlayers++;
	}

	// save network address for re-associating with reconnecting player, after stripping out port number
	FString Address = NewPlayer->GetPlayerNetworkAddress();
	int32 pos = Address.Find(TEXT(":"), ESearchCase::CaseSensitive);
	NewPlayer->PlayerState->SavedNetworkAddress = (pos > 0) ? Address.Left(pos) : Address;

	// check if this player is reconnecting and already has PlayerState
	FindInactivePlayer(NewPlayer);

	// Runs shared initialization that can happen during seamless travel as well

	GenericPlayerInitialization(NewPlayer);

	// Perform initialization that only happens on initially joining a server

	NewPlayer->ClientCapBandwidth(NewPlayer->Player->CurrentNetSpeed);

	if (MustSpectate(NewPlayer))
	{
		NewPlayer->ClientGotoState(NAME_Spectating);
	}
	else
	{
		// If NewPlayer is not only a spectator and has a valid ID, add him as a user to the replay.
		const FUniqueNetIdRepl& NewPlayerStateUniqueId = NewPlayer->PlayerState->GetUniqueId();
		if (NewPlayerStateUniqueId.IsValid())
		{
			GetGameInstance()->AddUserToReplay(NewPlayerStateUniqueId.ToString());
		}
	}

	if (GameSession)
	{
		GameSession->PostLogin(NewPlayer);
	}

	// Notify Blueprints that a new player has logged in.  Calling it here, because this is the first time that the PlayerController can take RPCs
	K2_PostLogin(NewPlayer);

	FGameModeEvents::GameModePostLoginEvent.Broadcast(this, NewPlayer);

	Cast<ANT_PlayerController>(NewPlayer)->On_OwningClient_PostLogin.AddDynamic(this, &ANT_GameMode::Server_OwningClient_PostLogin);
}
