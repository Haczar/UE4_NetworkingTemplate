// We need to see a lawyer.

#pragma once

// Unreal
#include "CoreMinimal.h"

// NT
#include "Utilities/UStatic_Util.h"

// UE Header Tool
#include "NetSlime_Static.generated.h"



// Enum

UENUM(BlueprintType)
enum class ENetScope : uint8
{
	Router,
	Server,
	ServerRPC,
	Client,
	ClientRPC,
	ReroutingClientRPC,
	Owner,
	Local
};

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_worldContext"))
	static bool ServerSide(UObject* _worldContext);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_worldContext"))
	static bool ClientSide(UObject* _worldContext);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_worldContext"))
	static ENetworkSystemRole ServerOrClient(UObject* _worldContext);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_worldContext"))
	static EServerType ServerType(UObject* _worldContext);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_worldContext"))
	static ENetworkMode NetworkMode(UObject* _worldContext);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Side", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
	static void K2_ServerSide(UObject* WorldContextObject, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Client Side", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
	static void K2_ClientSide(UObject* WorldContextObject, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Or Client", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
	static void K2_ServerOrClient(UObject* WorldContextObject, ENetworkSystemRole& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Type", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
	static void K2_ServerType(UObject* WorldContextObject, EServerType& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Network Mode", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
	static void K2_NetworkMode(UObject* WorldContextObject, ENetworkMode& ExecRoute);
};



UINTERFACE(MinimalAPI)
class UNetSlime : public UInterface
{
	GENERATED_BODY()

};

class NETWORKINGTEMPLATE_API INetSlime
{
	GENERATED_BODY()

public:


	virtual bool               ServerSide    () = NULL;
	virtual bool               ClientSide    () = NULL;
	virtual ENetworkSystemRole ServerOrClient() = NULL;
	virtual EServerType        ServerType    () = NULL;
	virtual ENetworkMode       NetworkMode   () = NULL;
};



#define INetSlime_Generate_Header() \
FORCEINLINE bool               ServerSide    () { return UNetSlime_Static::ServerSide    (GetWorld()); } \
FORCEINLINE bool               ClientSide    () { return UNetSlime_Static::ClientSide    (GetWorld()); } \
FORCEINLINE ENetworkSystemRole ServerOrClient() { return UNetSlime_Static::ServerOrClient(GetWorld()); } \
FORCEINLINE EServerType        ServerType    () { return UNetSlime_Static::ServerType    (GetWorld()); } \
FORCEINLINE ENetworkMode       NetworkMode   () { return UNetSlime_Static::NetworkMode   (GetWorld()); }
