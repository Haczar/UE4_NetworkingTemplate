// We need to see a lawyer.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "Logging/LogMacros.h"

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



NETWORKINGTEMPLATE_API DECLARE_LOG_CATEGORY_EXTERN(NetSlime, Log, All);



/**
 * NetSlime: Just a bunch of ease of use utilities for 
 */
UCLASS()
class NETWORKINGTEMPLATE_API UNetSlime_Static : public UStatic_Util
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "NetLog", CallableWithoutWorldContext, WorldContext = "_context"))
	static void Log(const UObject* _context, FString _messsage);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_context"))
	static bool ServerSide(const UObject* _context);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_context"))
	static bool ClientSide(const UObject* _context);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_context"))
	static ENetworkSystemRole ServerOrClient(const UObject* _context);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_context"))
	static EServerType ServerType(const UObject* _context);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (CallableWithoutWorldContext, WorldContext = "_context"))
	static ENetworkMode NetworkMode(const UObject* _context);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Side", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_ServerSide(const UObject* _context, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Client Side", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_ClientSide(const UObject* _context, EContinue& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Or Client", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_ServerOrClient(const UObject* _context, ENetworkSystemRole& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Server Type", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_ServerType(const UObject* _context, EServerType& ExecRoute);

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "Network Mode", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_NetworkMode(const UObject* _context, ENetworkMode& ExecRoute);

	// AActor related...

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (DisplayName = "Server Authorized", CallableWithoutWorldContext, WorldContext = "_context"))
	static bool ServerAuthorized(const UObject* _context);
		
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (DisplayName = "Is Owning Client", CallableWithoutWorldContext, WorldContext = "_context"))
	static bool IsOwningClient(const UObject* _context);

	// Has access to server RPCs. Does not care if your not the owner.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Server Authorized", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "_context"))
	static void K2_ServerAuthorized(const UObject* _context, EIsResult& ExecRoute);

	// Has access to server RPCs, and is the designated client responsible for the actor.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Is Owning Client", CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute",  WorldContext = "_context"))
	static void K2_IsOwningClient(const UObject* _context, EIsResult& ExecRoute);
};



// Interface
// If you need to deal with a large set of objects and have access to net slime generically.

UINTERFACE(MinimalAPI)
class UNetSlime : public UInterface
{
	GENERATED_BODY()
};

class NETWORKINGTEMPLATE_API INetSlime
{
	GENERATED_BODY()

public:

	virtual void NetLog(FString _message) = NULL;

	virtual bool               ServerSide    () = NULL;
	virtual bool               ClientSide    () = NULL;
	virtual ENetworkSystemRole ServerOrClient() = NULL;
	virtual EServerType        ServerType    () = NULL;
	virtual ENetworkMode       NetworkMode   () = NULL;

	// Actor related

	virtual bool ServerAuthorized() = NULL;
	virtual bool IsOwningClient  () = NULL;
};


// Quick way to generate functions for anything that wants easy access to NetSlime.
#define INetSlime_Generate_Header() \
FORCEINLINE void               NetLog          (FString _message) { return UNetSlime_Static::Log             (this, _message); } \
FORCEINLINE bool               ServerSide      ()                 { return UNetSlime_Static::ServerSide      (this);           } \
FORCEINLINE bool               ClientSide      ()                 { return UNetSlime_Static::ClientSide      (this);           } \
FORCEINLINE ENetworkSystemRole ServerOrClient  ()                 { return UNetSlime_Static::ServerOrClient  (this);           } \
FORCEINLINE EServerType        ServerType      ()                 { return UNetSlime_Static::ServerType      (this);           } \
FORCEINLINE ENetworkMode       NetworkMode     ()                 { return UNetSlime_Static::NetworkMode     (this);           } \
FORCEINLINE bool               ServerAuthorized()                 { return UNetSlime_Static::ServerAuthorized(this);           } \
FORCEINLINE bool               IsOwningClient  ()                 { return UNetSlime_Static::IsOwningClient  (this);           }

