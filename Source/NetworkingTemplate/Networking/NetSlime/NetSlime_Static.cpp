// We need to see a lawyer.

// Parent Header
#include "NetSlime_Static.h"

// Unreal
#include "Components/ActorComponent.h"



DEFINE_LOG_CATEGORY(NetSlime);



// Private

FString GetNetworkModeStr(const UObject* _context)
{
	FString mode;

	switch (UNetSlime_Static::NetworkMode(_context))
	{
		case ENetworkMode::Standalone:
		{
			mode = TEXT("Standalone");

			break;
		}
		case ENetworkMode::ListenServer:
		{
			mode = TEXT("ListenServer");

			break;
		}
		case ENetworkMode::DedicatedServer:
		{
			mode = TEXT("DedicatedServer");

			break;
		}
		case ENetworkMode::Client:
		{
			mode = TEXT("Client");

			break;
		}
	}

	return mode;
}


// Public

void UNetSlime_Static::Log(const UObject* _context, FString _message)
{
	FString mode = GetNetworkModeStr(_context);

	const AActor*            actorRef  = nullptr;
	const APlayerController* playerRef = nullptr;

	if (_context->GetClass()->IsChildOf(AActor::StaticClass()))
	{
		actorRef  = Cast<AActor>(_context);
	}
	else if (_context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
	{
		const UActorComponent* compActor = Cast<UActorComponent>(_context);

		actorRef = compActor->GetOwner();
	}

	FString actorLevel;

	if (actorRef)
	{
		if (! actorRef->IsA(APlayerController::StaticClass()))
		{
			if (actorRef->HasNetOwner())
			{
				playerRef = actorRef->GetOwner()->GetNetOwningPlayer()->GetPlayerController(_context->GetWorld());
			}
		}
		else
		{
			playerRef = Cast<APlayerController>(actorRef);
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

		

		if (actorRef->HasNetOwner() && IsOwningClient(actorRef))
		{
			actorLevel = TEXT("Owning Client");
		}
		else if (ServerAuthorized(actorRef))
		{
			actorLevel = TEXT("Server Authorized");
		}
		else
		{
			actorLevel = TEXT("No Authority");
		}
	}
	else
	{
		actorLevel = TEXT("Local");
	}

	mode       = FString::Printf(TEXT("%-16s"), *mode);
	actorLevel = FString::Printf(TEXT("%-18s"), *actorLevel);

	FString name = FString::Printf(TEXT("%-30s"), *_context->GetName());

	SET_WARN_COLOR(COLOR_PURPLE)

		UE_LOG(NetSlime, Log, TEXT("%s %s %s : %s"), *mode, *actorLevel, *name, *_message);

	CLEAR_WARN_COLOR()
}

bool UNetSlime_Static::ServerSide(const UObject* _worldContext)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContext, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UNetSlime_Static::ClientSide(const UObject* _worldContext)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContext, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ENetworkSystemRole UNetSlime_Static::ServerOrClient(const UObject* _worldContext)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContext, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == true)
	{
		return ENetworkSystemRole::Server;
	}
	else
	{
		return ENetworkSystemRole::Client;
	}
}

EServerType UNetSlime_Static::ServerType(const UObject* _worldContext)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContext, EGetWorldErrorMode::ReturnNull);

	switch (WorldRef->GetNetMode())
	{
		case ENetMode::NM_Standalone:
		{
			return EServerType::Standalone;
		}
		case ENetMode::NM_DedicatedServer:
		{
			return EServerType::DedicatedServer;
		}
		case ENetMode::NM_ListenServer:
		{
			return EServerType::ListenServer;
		}
		default:
		{
			return EServerType::NotServer;
		}
	}
}

ENetworkMode UNetSlime_Static::NetworkMode(const UObject* _worldContext)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContext, EGetWorldErrorMode::ReturnNull);

	switch (WorldRef->GetNetMode())
	{
		case ENetMode::NM_Standalone:
		{
			return ENetworkMode::Standalone;

		}
		case ENetMode::NM_DedicatedServer:
		{
			return ENetworkMode::DedicatedServer;
		}
		case ENetMode::NM_ListenServer:
		{
			return ENetworkMode::ListenServer;
		}
		case ENetMode::NM_Client:
		{
			return ENetworkMode::Client;
		}

		// SHould NEVER HAPPEN.
		default:
		{
			return ENetworkMode::Standalone;
		}
	}
}

void UNetSlime_Static::K2_ServerSide(const UObject* WorldContextObject, EContinue& ExecRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == true)
	{
		ExecRoute = EContinue::Continue;

		return;
	}
	else
	{
		ExecRoute = EContinue::_;

		return;
	}
}

void UNetSlime_Static::K2_ClientSide(const UObject* _worldContextObject, EContinue& _execRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(_worldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == false)
	{

		_execRoute = EContinue::Continue;

		return;
	}
	else
	{
		_execRoute = EContinue::_;

		return;
	}
}

void UNetSlime_Static::K2_ServerOrClient(const UObject* WorldContextObject, ENetworkSystemRole& ExecRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == true)
	{
		ExecRoute = ENetworkSystemRole::Server;

		return;
	}
	else
	{
		ExecRoute = ENetworkSystemRole::Client;

		return;
	}
}

void UNetSlime_Static::K2_ServerType(const UObject* WorldContextObject, EServerType& ExecRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	switch (WorldRef->GetNetMode())
	{
		case ENetMode::NM_Standalone:
		{
			ExecRoute = EServerType::Standalone;

			return;
		}
		case ENetMode::NM_DedicatedServer:
		{
			ExecRoute = EServerType::DedicatedServer;

			return;
		}
		case ENetMode::NM_ListenServer:
		{
			ExecRoute = EServerType::ListenServer;

			return;
		}
		default:
		{
			return;
		}
	}
}

void UNetSlime_Static::K2_NetworkMode(const UObject* WorldContextObject, ENetworkMode& ExecRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	switch (WorldRef->GetNetMode())
	{
		case ENetMode::NM_Standalone:
		{
			ExecRoute = ENetworkMode::Standalone;

			return;
		}
		case ENetMode::NM_DedicatedServer:
		{
			ExecRoute = ENetworkMode::DedicatedServer;

			return;
		}
		case ENetMode::NM_ListenServer:
		{
			ExecRoute = ENetworkMode::ListenServer;

			return;
		}
		case ENetMode::NM_Client:
		{
			ExecRoute = ENetworkMode::Client;

			return;
		}
	}
}



// AActor Related

bool UNetSlime_Static::ServerAuthorized(const UObject* _context)
{
	ENetMode networkInstance = _context->GetWorld()->GetNetMode();

	FString mode = GetNetworkModeStr(_context);

	const AActor*            actorRef  = nullptr;
	const APlayerController* playerRef = nullptr;

	if (_context->IsA(AActor::StaticClass()))
	{
		actorRef = Cast<AActor>(_context);
	}
	else if (_context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
	{
		const UActorComponent* compActor = Cast<UActorComponent>(_context);

		actorRef = compActor->GetOwner();
	}

	if (actorRef == nullptr)
	{
		SET_WARN_COLOR(COLOR_PURPLE)

			FString message = TEXT("Must be an actor to use ServerAuthorized check.");

		UE_LOG(NetSlime, Error, TEXT("%s:  %s in [%s]"), *mode, *message, *_context->GetName());

		CLEAR_WARN_COLOR()

			return false;
	}

	if (! actorRef->IsA(APlayerController::StaticClass()))
	{
		if (actorRef->GetOwner())
		{
			playerRef = actorRef->GetOwner()->GetNetOwningPlayer()->GetPlayerController(_context->GetWorld());
		}	
	}
	else
	{
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

bool UNetSlime_Static::IsOwningClient(const UObject* _context)
{
	ENetMode networkInstance = _context->GetWorld()->GetNetMode();

	FString mode = GetNetworkModeStr(_context);

	const AActor*            actorRef  = nullptr;
	const APlayerController* playerRef = nullptr;

	if (_context->IsA(AActor::StaticClass()))
	{
		actorRef = Cast<AActor>(_context);
	}
	else if (_context->GetClass()->IsChildOf(UActorComponent::StaticClass()))
	{
		const UActorComponent* compActor = Cast<UActorComponent>(_context);

		actorRef = compActor->GetOwner();
	}

	if (actorRef == nullptr)
	{
		SET_WARN_COLOR(COLOR_PURPLE)

			FString message = TEXT("Must be an actor to use IsOwningClient check.");

		UE_LOG(NetSlime, Error, TEXT("%s:  %s in [%s]"), *mode, *message, *_context->GetName());

		CLEAR_WARN_COLOR()

			return false;
	}

	if (!actorRef->HasNetOwner())
	{
		SET_WARN_COLOR(COLOR_PURPLE)

			FString message = TEXT("Must have net owner in order to determine if owning client.");

			UE_LOG(NetSlime, Error, TEXT("%s:  %s in [%s]"), *mode, *message, *_context->GetName());

		CLEAR_WARN_COLOR()

		return false;
	}

	if (! actorRef->IsA(APlayerController::StaticClass()))
	{
		playerRef = actorRef->GetOwner()->GetNetOwningPlayer()->GetPlayerController(_context->GetWorld());
	}
	else
	{
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

void UNetSlime_Static::K2_ServerAuthorized(const UObject* _context, EIsResult& _execRoute)
{
	if (ServerAuthorized(_context))
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

void UNetSlime_Static::K2_IsOwningClient(const UObject* _context, EIsResult& _execRoute)
{
	if (IsOwningClient(_context))
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
