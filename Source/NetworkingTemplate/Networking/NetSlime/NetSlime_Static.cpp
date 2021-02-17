// We need to see a lawyer.

// Parent Header
#include "NetSlime_Static.h"

// Unreal



// Public

bool UNetSlime_Static::ServerSide(UObject* _worldContext)
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

bool UNetSlime_Static::ClientSide(UObject* _worldContext)
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

ENetworkSystemRole UNetSlime_Static::ServerOrClient(UObject* _worldContext)
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

EServerType UNetSlime_Static::ServerType(UObject* _worldContext)
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

ENetworkMode UNetSlime_Static::NetworkMode(UObject* _worldContext)
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

void UNetSlime_Static::K2_ServerSide(UObject* WorldContextObject, EContinue& ExecRoute)
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

void UNetSlime_Static::K2_ClientSide(UObject* _worldContextObject, EContinue& _execRoute)
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

void UNetSlime_Static::K2_ServerOrClient(UObject* WorldContextObject, ENetworkSystemRole& ExecRoute)
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

void UNetSlime_Static::K2_ServerType(UObject* WorldContextObject, EServerType& ExecRoute)
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

void UNetSlime_Static::K2_NetworkMode(UObject* WorldContextObject, ENetworkMode& ExecRoute)
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
