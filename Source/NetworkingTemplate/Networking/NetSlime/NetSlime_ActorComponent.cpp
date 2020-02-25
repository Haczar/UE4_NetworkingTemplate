// We need to see a lawyer.

// Parent Header
#include "NetSlime_ActorComponent.h"

// Include

// Unreal Engine
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Player.h"



// Sets default values for this component's properties
UNetSlime_ActorComponent::UNetSlime_ActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UNetSlime_ActorComponent::ServerAuthorized(UObject* _worldContextObject, EIsResult &ExecRoute)
{
	ENetMode networkInstance = _worldContextObject->GetWorld()->GetNetMode();

	AActor* actorCast = GetOwner();

	ENetRole ownerRole = this->GetOwnerRole();

	ENetRole netRoleInstance   = GetOwner()->GetLocalRole ();
	ENetRole netRoleRemoteInst = GetOwner()->GetRemoteRole();

	UE_LOG(LogTemp, Warning, TEXT("Role: %d"), netRoleRemoteInst);

	switch (networkInstance)
	{
	case NM_Standalone:
	{
		ExecRoute = EIsResult::Yes;

		return;
	}
	case NM_DedicatedServer:
	{
		ExecRoute = EIsResult::Yes;

		return;
	}
	case NM_ListenServer:
	{
		ExecRoute = EIsResult::Yes;

		return;		
	}
	case NM_Client:
	{
		if (netRoleInstance == ROLE_AutonomousProxy)
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
	case NM_MAX:
	{
		ExecRoute = EIsResult::No;

		return;
	}
	}

	//if (netRoleInstance == ROLE_Authority)
		//{
		//	// Local authority in control.
		//	ExecRoute = EIsResult::Yes;

		//	return;
		//}
		//else
		//{
		//	ExecRoute = EIsResult::Yes;

		//	return;
		//}
}

void UNetSlime_ActorComponent::IsOwningClient(UObject* _worldContextObject, EIsResult& _execRoute)
{
	ENetMode networkInstance = _worldContextObject->GetWorld()->GetNetMode();

	if (!GetOwner()->HasNetOwner())
	{
		UE_LOG(LogTemp, Error, TEXT("Must have net owner in order to determine if owning client."));
	}

	UWorld* worldRef = _worldContextObject->GetWorld();

	AActor*            actorRef  = GetOwner()                                                     ;
	APlayerController* playerRef = GetOwner()->GetNetOwningPlayer()->GetPlayerController(worldRef);

	ENetRole netRoleInstance;
	ENetRole netRoleRemoteInst;

	if (playerRef != nullptr)
	{
		netRoleInstance   = playerRef->Role;
		netRoleRemoteInst = playerRef->GetRemoteRole();
	}
	else
	{
		netRoleInstance   = actorRef->Role           ;
		netRoleRemoteInst = actorRef->GetRemoteRole();
	}
	
	switch (networkInstance)
	{
		case NM_Client:
		{
			if (netRoleInstance == ROLE_AutonomousProxy)
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
		case NM_ListenServer:
		{
			if (netRoleInstance == ROLE_Authority)
			{
				if (netRoleRemoteInst != ROLE_AutonomousProxy)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Owning client check passed for listen server..."));

					_execRoute = EIsResult::Yes;
				}
				else
				{
					_execRoute = EIsResult::No;
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

				return;
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("Owning client check failed for listen server..."));

				_execRoute = EIsResult::No;

				return;
			}
		}
		case NM_Standalone:
		{
			_execRoute = EIsResult::Yes;

			return;
		}
		default:
		{
			_execRoute = EIsResult::No;

			return;
		}
	}
}
