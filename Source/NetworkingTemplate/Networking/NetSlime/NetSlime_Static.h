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


UINTERFACE(BlueprintType)
class UNetSlime : public UInterface
{
	GENERATED_BODY()

};

class NETWORKINGTEMPLATE_API INetSlime
{
	GENERATED_BODY()

public:


	UFUNCTION(Category = "Net Slime", BlueprintCallable, BlueprintNativeEvent) 
	bool ServerSide();
	UFUNCTION(Category = "Net Slime", BlueprintCallable, BlueprintNativeEvent) 
	bool               ClientSide    ();
	UFUNCTION(Category = "Net Slime", BlueprintCallable, BlueprintNativeEvent) 
	ENetworkSystemRole ServerOrClient();
	UFUNCTION(Category = "Net Slime", BlueprintCallable, BlueprintNativeEvent) 
	EServerType        ServerType    ();
	UFUNCTION(Category = "Net Slime", BlueprintCallable, BlueprintNativeEvent) 
	ENetworkMode       NetworkMode   ();
};


#define UNetSlime_DumpCppDefsForClass() \
FORCEINLINE bool               ServerSide    () { return UNetSlime_Static::ServerSide    (GetWorld()); } \
FORCEINLINE bool               ClientSide    () { return UNetSlime_Static::ClientSide    (GetWorld()); } \
FORCEINLINE ENetworkSystemRole ServerOrClient() { return UNetSlime_Static::ServerOrClient(GetWorld()); } \
FORCEINLINE EServerType        ServerType    () { return UNetSlime_Static::ServerType    (GetWorld()); } \
FORCEINLINE ENetworkMode       NetworkMode   () { return UNetSlime_Static::NetworkMode   (GetWorld()); }

// This allows for Net Slime static functionality to be  called without 
// having to reference the class or provide a world context for the class that has this macro in its header body.
#define INetSlime_Generate_Header() \
virtual bool               ServerSide_Implementation    () override; \
virtual bool               ClientSide_Implementation    () override; \
virtual ENetworkSystemRole ServerOrClient_Implementation() override; \
virtual EServerType        ServerType_Implementation    () override; \
virtual ENetworkMode       NetworkMode_Implementation   () override; 



#define INetSlime_Generate_Implementation(_className) \
bool _className::ServerSide_Implementation    () { return UNetSlime_Static::ServerSide(GetWorld() ); } \
bool _className::ClientSide_Implementation    () { return UNetSlime_Static::ClientSide(GetWorld() ); } \
ENetworkSystemRole _className::ServerOrClient_Implementation() { return UNetSlime_Static::ServerOrClient(GetWorld() ); } \
EServerType _className::ServerType_Implementation    () { return UNetSlime_Static::ServerType(GetWorld() ); } \
ENetworkMode _className::NetworkMode_Implementation   () { return UNetSlime_Static::NetworkMode(GetWorld() ); }



