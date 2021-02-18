// We need to see a lawyer.

// Parent Header
#include "NetSlime_Actor.h"

// Unreal Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Player.h"

// NT
#include "NetSlime_Static.h"



// Sets default values for this component's properties
UNetSlime_Actor::UNetSlime_Actor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

bool UNetSlime_Actor::ServerAuthorized_Static(AActor* _actor)
{
	ENetMode networkInstance = _actor->GetWorld()->GetNetMode();

	const APlayerController* playerRef = nullptr;

	if (! _actor->IsA(APlayerController::StaticClass()))
	{
		if (! _actor->GetOwner())
		{
			playerRef = _actor->GetOwner()->GetNetOwningPlayer()->GetPlayerController(_actor->GetWorld());
		}	
	}
	else
	{
		playerRef = Cast<APlayerController>(_actor);
	}

	ENetRole netRoleInstance   = ENetRole::ROLE_None;
	ENetRole netRoleRemoteInst = ENetRole::ROLE_None;

	if (playerRef != nullptr)
	{
		netRoleInstance   = playerRef->GetLocalRole ();
		netRoleRemoteInst = playerRef->GetRemoteRole();
	}
	else
	{
		netRoleInstance   = _actor->GetLocalRole ();
		netRoleRemoteInst = _actor->GetRemoteRole();
	}

	switch (networkInstance)
	{
		case NM_Client:
		{
			if (netRoleInstance == ROLE_AutonomousProxy)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		case NM_ListenServer:
		{
			return true;
		}
		case NM_DedicatedServer:
		{
			return true;
		}
		case NM_Standalone:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

bool UNetSlime_Actor::IsOwningClient_Static(AActor* _actor)
{
	ENetMode networkInstance = _actor->GetWorld()->GetNetMode();

	if (!_actor->HasNetOwner())
	{
		Log_Static(_actor, "Must have net owner in order to determine if owning client.");
	}

	const APlayerController* playerRef = nullptr;

	if (! _actor->IsA(APlayerController::StaticClass()))
	{
		playerRef = _actor->GetOwner()->GetNetOwningPlayer()->GetPlayerController(_actor->GetWorld());
	}
	else
	{
		playerRef = Cast<APlayerController>(_actor);
	}

	ENetRole netRoleInstance   = ENetRole::ROLE_None;
	ENetRole netRoleRemoteInst = ENetRole::ROLE_None;

	if (playerRef != nullptr)
	{
		netRoleInstance   = playerRef->GetLocalRole ();
		netRoleRemoteInst = playerRef->GetRemoteRole();
	}
	else
	{
		netRoleInstance   = _actor->GetLocalRole ();
		netRoleRemoteInst = _actor->GetRemoteRole();
	}

	switch (networkInstance)
	{
		case NM_Client:
		{
			if (netRoleInstance == ROLE_AutonomousProxy)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		case NM_ListenServer:
		{
			if (netRoleInstance == ROLE_Authority)
			{
				if (netRoleRemoteInst != ROLE_AutonomousProxy)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		case NM_Standalone:
		{
			return true;
		}
		default:
		{
			return false;
		}
	}
}

void UNetSlime_Actor::Log_Static(AActor* _context, FString _message)
{
	const AActor*            actorRef  = nullptr;
	const APlayerController* playerRef = nullptr;

	if (! _context->IsA(APlayerController::StaticClass()))
	{
		actorRef  = _context->GetOwner();
		playerRef = _context->GetOwner()->GetNetOwningPlayer()->GetPlayerController(actorRef->GetWorld());
	}
	else
	{
		actorRef  = _context;
		playerRef = Cast<APlayerController>(_context);
	}

	ENetRole netRoleInstance   = ENetRole::ROLE_None;
	ENetRole netRoleRemoteInst = ENetRole::ROLE_None;

	if (playerRef != nullptr)
	{
		netRoleInstance   = playerRef->GetLocalRole ();
		netRoleRemoteInst = playerRef->GetRemoteRole();
	}
	else
	{
		netRoleInstance   = actorRef->GetLocalRole ();
		netRoleRemoteInst = actorRef->GetRemoteRole();
	}

	FString mode;

	switch (UNetSlime_Static::NetworkMode(_context))
	{
		case ENetworkMode::Standalone:
		{
			mode = TEXT("Standalone     ");

			break;
		}
		case ENetworkMode::ListenServer:
		{
			mode = TEXT("ListenServer   ");

			break;
		}
		case ENetworkMode::DedicatedServer:
		{
			mode = TEXT("DedicatedServer");

			break;
		}
		case ENetworkMode::Client:
		{
			mode = TEXT("Client         ");

			break;
		}
	}

	FString actorLevel;

	if (IsOwningClient_Static(_context))
	{
		actorLevel = TEXT("Server Authorized");
	}
	else if (ServerAuthorized_Static(_context))
	{
		actorLevel = TEXT("Owning Client");
	}
	else
	{
		actorLevel = TEXT("No Authority");
	}

	_message = FString::Printf(TEXT("%-60s"), *_message);

	SET_WARN_COLOR(COLOR_PURPLE)

		UE_LOG(NetSlime, Log, TEXT("%s:  %s in [%s] Net Level: %s"), *mode, *_message, *_context->GetName(), *actorLevel);

	CLEAR_WARN_COLOR()
}

bool UNetSlime_Actor::ServerAuthorized()
{
	return ServerAuthorized_Static(this->GetOwner());
}

bool UNetSlime_Actor::IsOwningClient()
{
	return IsOwningClient_Static(this->GetOwner());
}

void UNetSlime_Actor::Log(FString _message)
{
	Log_Static(this->GetOwner(), _message);
}

void UNetSlime_Actor::K2_ServerAuthorized(EIsResult& _execRoute)
{
	if (ServerAuthorized())
	{
		_execRoute = EIsResult::Yes;

		return;
	}
	else
	{
		_execRoute = EIsResult::No;

		return;
	}
}

void UNetSlime_Actor::K2_IsOwningClient(EIsResult& _execRoute)
{
	if (IsOwningClient())
	{
		_execRoute = EIsResult::Yes;

		return;
	}
	else
	{
		_execRoute = EIsResult::No;

		return;
	}
}
