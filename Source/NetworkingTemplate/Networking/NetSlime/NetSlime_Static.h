// We need to see a lawyer.

#pragma once

// Includes

// Unreal
#include "CoreMinimal.h"

// Networking
#include "Engine/NetworkDelegates.h"
#include "Net/UnrealNetwork.h"
#include "Net/RepLayout.h"

// Phantom
#include "Utilities/UStatic_Util.h"

// UE Header Tool
#include "NetSlime_Static.generated.h"



// Enum

UENUM(BlueprintType)
enum class ENetworkSystemRole : uint8
{
	Server,
	Client
};

UENUM(BlueprintType)
enum class ENetworkType : uint8
{
	Dedicated   ,
	Local_Server
};

UENUM(BlueprintType)
enum class EServerType : uint8
{
	Standalone,
	DedicatedServer,
	ListenServer,
	NotServer
};

UENUM(BlueprintType)
enum class ENetworkMode : uint8
{
	Standalone,
	DedicatedServer,
	ListenServer,
	Client
};



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API UNetSlime_Static : public UStatic_Util
{
	GENERATED_BODY()

public:

	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime")

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "WorldContextObject"))
		static EServerType ServerType_Pure(UObject* WorldContextObject);

	//UFUNCTION(BlueprintCallable,  Category = "Net Slime", Meta = (ExpandEnumAsExecs = "ExecRoute", CallableWithoutWorldContext, WorldContext = "WorldContextObject"))

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		static void ServerSide(UObject* WorldContextObject, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		static void ClientSide(UObject* WorldContextObject, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		static void ServerOrClient(UObject* WorldContextObject, ENetworkSystemRole& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		static void ServerType(UObject* WorldContextObject, EServerType& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		static void NetworkMode(UObject* WorldContextObject, ENetworkMode& ExecRoute);
};
