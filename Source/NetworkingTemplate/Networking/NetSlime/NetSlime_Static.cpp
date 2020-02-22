// We need to see a lawyer.

// Parent Header
#include "NetSlime_Static.h"

// Unreal

//#include "OnlineSubsystemImpl.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/Engine.h"
#include "Engine/World.h"



EServerType UNetSlime_Static::ServerType_Pure(UObject* WorldContextObject)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

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

void UNetSlime_Static::ServerSide(UObject* WorldContextObject, EContinue& ExecRoute)
{
	UWorld* WorldRef = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::ReturnNull);

	if (WorldRef->IsServer() == true)
	{
		ExecRoute = EContinue::Continue;

		return;
	}
	else
	{
		// Add log stuff here...

		ExecRoute = EContinue::_;

		return;
	}

}

void UNetSlime_Static::ClientSide(UObject* _worldContextObject, EContinue& _execRoute)
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

void UNetSlime_Static::ServerOrClient(UObject* WorldContextObject, ENetworkSystemRole& ExecRoute)
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

void UNetSlime_Static::ServerType(UObject* WorldContextObject, EServerType& ExecRoute)
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

void UNetSlime_Static::NetworkMode(UObject* WorldContextObject, ENetworkMode& ExecRoute)
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
