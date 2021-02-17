// We need to see a lawyer.

// Parent Header
#include "NetSlime_Actor.h"

// Include

// Unreal Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Player.h"





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

	if (!_actor->GetOwner()->HasNetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Must have net owner in order to determine if owning client."));
	}

	UWorld* worldRef = _actor->GetWorld();

	const AActor*            actorRef  = _actor->GetOwner();
	const APlayerController* playerRef = _actor->GetOwner()->GetNetOwningPlayer()->GetPlayerController(worldRef);

	ENetRole netRoleInstance;
	ENetRole netRoleRemoteInst;

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
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					return true;
				}
				else
				{
					return false;
				}

			#if UE_EDITOR == true
				// Carlos: listenserver showed up with simulatedproxy role on my end (regardless of single process on/off)
				// DO NOT USE SINGLE PROCESS WHILE TESTING SINGLE INSTANCE.
				//if (netRoleRemoteInst != ROLE_AutonomousProxy)
				//{
				//	//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

				//	_execRoute = EIsResult::Yes; 
				//}
				//else
				//{
				//	_execRoute = EIsResult::No;
				//}

			#endif

				//On Oculus Quest its not equal, on editor its equal. TODO: (Note we don't know if its actually android or not...)
			#if UE_GAME == true

				if (netRoleRemoteInst != ROLE_AutonomousProxy)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					_execRoute = EIsResult::Yes;
				}
				else
				{
					_execRoute = EIsResult::No;
				}

			#endif

				return false;
			}
			else
			{
				return false;
			}
		}
		case NM_Standalone:
		{
			return false;
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
		UE_LOG(LogTemp, Error, TEXT("Must have net owner in order to determine if owning client."));
	}

	UWorld* worldRef = _actor->GetWorld();

	const AActor*            actorRef  = nullptr;
	const APlayerController* playerRef = nullptr;

	if (! _actor->IsA(APlayerController::StaticClass()))
	{
		actorRef  = _actor->GetOwner();
		playerRef = _actor->GetOwner()->GetNetOwningPlayer()->GetPlayerController(worldRef);
	}
	else
	{
		actorRef  = _actor;
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
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					return true;
				}
				else
				{
					return false;
				}

			#if UE_EDITOR == true
				// Carlos: listenserver showed up with simulatedproxy role on my end (regardless of single process on/off)
				// DO NOT USE SINGLE PROCESS WHILE TESTING SINGLE INSTANCE.
				//if (netRoleRemoteInst != ROLE_AutonomousProxy)
				//{
				//	//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

				//	_execRoute = EIsResult::Yes; 
				//}
				//else
				//{
				//	_execRoute = EIsResult::No;
				//}

			#endif

				//On Oculus Quest its not equal, on editor its equal. TODO: (Note we don't know if its actually android or not...)
			#if UE_GAME == true

				if (netRoleRemoteInst != ROLE_AutonomousProxy)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					_execRoute = EIsResult::Yes;
				}
				else
				{
					_execRoute = EIsResult::No;
				}

			#endif

				return false;
			}
			else
			{
				return false;
			}
		}
		case NM_Standalone:
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
}

bool UNetSlime_Actor::ServerAuthorized()
{
	ENetMode networkInstance = GetWorld()->GetNetMode();

	switch (networkInstance)
	{
		case NM_Standalone:
		{
			return true;
		}
		case NM_DedicatedServer:
		{
			return true;
		}
		case NM_ListenServer:
		{
			return true;
		}
		case NM_Client:
		{
			AActor* actorCast = GetOwner();

			ENetRole ownerRole = this->GetOwnerRole();

			ENetRole netRoleInstance   = GetOwner()->GetLocalRole ();
			ENetRole netRoleRemoteInst = GetOwner()->GetRemoteRole();

			if (netRoleInstance == ROLE_AutonomousProxy)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		case NM_MAX:
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
}

bool UNetSlime_Actor::IsOwningClient()
{
	ENetMode networkInstance = GetWorld()->GetNetMode();

	if (!GetOwner()->HasNetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Must have net owner in order to determine if owning client."));
	}

	UWorld* worldRef = GetWorld();

	const AActor* actorRef             = GetOwner();
	const APlayerController* playerRef = GetOwner()->GetNetOwningPlayer()->GetPlayerController(worldRef);

	ENetRole netRoleInstance;
	ENetRole netRoleRemoteInst;

	if (playerRef != nullptr)
	{
		netRoleInstance = playerRef->GetLocalRole ();
		netRoleRemoteInst = playerRef->GetRemoteRole();
	}
	else
	{
		netRoleInstance = actorRef->GetLocalRole ();
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
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					return true;
				}
				else
				{
					return false;
				}

			#if UE_EDITOR == true
				// Carlos: listenserver showed up with simulatedproxy role on my end (regardless of single process on/off)
				// DO NOT USE SINGLE PROCESS WHILE TESTING SINGLE INSTANCE.
				//if (netRoleRemoteInst != ROLE_AutonomousProxy)
				//{
				//	//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

				//	_execRoute = EIsResult::Yes; 
				//}
				//else
				//{
				//	_execRoute = EIsResult::No;
				//}

			#endif

				//On Oculus Quest its not equal, on editor its equal. TODO: (Note we don't know if its actually android or not...)
			#if UE_GAME == true

				if (netRoleRemoteInst != ROLE_AutonomousProxy)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					_execRoute = EIsResult::Yes;
				}
				else
				{
					_execRoute = EIsResult::No;
				}

			#endif

				return false;
			}
			else
			{
				return false;
			}
		}
		case NM_Standalone:
		{
			return false;
		}
		default:
		{
			return false;
		}
	}
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
