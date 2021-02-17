// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_PlayerController.h"

// Unreal
#include "GameFramework/PlayerState.h"

// NT

#include "NT_GameInstance.h"







// Public

void ANT_PlayerController::K2_IsOwningClient(EIsResult& ExecRoute)
{ 
	if (IsOwningClient()) 
	{ 
		ExecRoute = EIsResult::Yes; 

		return;
	} 
	else 
	{ 
		ExecRoute = EIsResult::No; 

		return;
	} 
}

ANT_PlayerController::ANT_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Protected

void ANT_PlayerController::Local_OnFrameworkInitialized()
{
	UE_LOG(LogTemp, Log, TEXT("NT PlayerController: Received framework initialization."));

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

	K2_Local_OnFrameworkInitialized();
}

void ANT_PlayerController::Server_SetOwningClient_FrameworkInitialized()
{
	bOwningClient_FrameworkInitialized = true;

	On_OwningClient_PostLogin.Broadcast(this);
}

void ANT_PlayerController::ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient_Implementation()
{
	if (ServerSide())
	{
		Server_SetOwningClient_FrameworkInitialized();
	}
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

//void ANT_PlayerController::OnPossess(APawn* aPawn)
//{
//	if (UNetSlime_Static::K2_ServerSide(GetWorld()))
//	{
//
//	}
//}



// AActor

// Public

void ANT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Log, TEXT("NT PlayerController: BeginPlay"));

	UNT_GameInstance* gInst = GetGameInstance<UNT_GameInstance>();

	gInst->Framework_Initialized.AddDynamic(this, &ANT_PlayerController::Local_OnFrameworkInitialized);

	gInst->Local_NotifyComponentReady(EFramework_ComponentFlag::PlayerController);
}

void ANT_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANT_PlayerController, bOwningClient_FrameworkInitialized);
}
