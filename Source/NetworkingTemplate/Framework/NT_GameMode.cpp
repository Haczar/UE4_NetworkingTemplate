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

void ANT_GameMode::PostLogin(APlayerController* _newPlayer)
{
	//Super::PostLogin()

	UWorld* world = GetWorld();

	// Update player count
	if (MustSpectate(_newPlayer))
	{
		NumSpectators++;
	}
	else if (world->IsInSeamlessTravel() || _newPlayer->HasClientLoadedCurrentWorld())
	{
		NumPlayers++;
	}
	else
	{
		NumTravellingPlayers++;
	}

	// Save network address for re-associating with reconnecting player, after stripping out port number
	FString address = _newPlayer->GetPlayerNetworkAddress();

	int32 pos = address.Find(TEXT(":"), ESearchCase::CaseSensitive);

	_newPlayer->PlayerState->SavedNetworkAddress = (pos > 0) ? address.Left(pos) : address;

	// Check if this player is reconnecting and already has PlayerState
	FindInactivePlayer(_newPlayer);

	// Runs shared initialization that can happen during seamless travel as well

	GenericPlayerInitialization(_newPlayer);

	// Perform initialization that only happens on initially joining a server

	_newPlayer->ClientCapBandwidth(_newPlayer->Player->CurrentNetSpeed);

	if (MustSpectate(_newPlayer))
	{
		_newPlayer->ClientGotoState(NAME_Spectating);
	}
	else
	{
		// If NewPlayer is not only a spectator and has a valid ID, add him as a user to the replay.
		const FUniqueNetIdRepl& newPlayerStateUniqueId = _newPlayer->PlayerState->GetUniqueId();

		if (newPlayerStateUniqueId.IsValid())
		{
			GetGameInstance()->AddUserToReplay(newPlayerStateUniqueId.ToString());
		}
	}

	if (GameSession)
	{
		GameSession->PostLogin(_newPlayer);
	}

	// Notify Blueprints that a new player has logged in.  Calling it here, because this is the first time that the PlayerController can take RPCs
	K2_PostLogin(_newPlayer);

	FGameModeEvents::GameModePostLoginEvent.Broadcast(this, _newPlayer);

	Cast<ANT_PlayerController>(_newPlayer)->On_OwningClient_PostLogin.AddDynamic(this, &ANT_GameMode::Server_OwningClient_PostLogin);
}
