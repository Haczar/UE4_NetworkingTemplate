// We need to see a lawyer.

#pragma once

// Include

// Unreal
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Phantom
#include "Utilities/UStatic_Util.h"
#include <Interface.h>

// UE Header Tool
#include "NetSlime_Actor.generated.h"



// Look into make a net slime actor class as well.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETWORKINGTEMPLATE_API UNetSlime_Actor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetSlime_Actor();

	static bool ServerAuthorized_Static(AActor* _contextWithOwner);
	static bool IsOwningClient_Static  (AActor* _contextWithOwner);
	static void Log_Static             (AActor* _contextWithOwner, FString _message);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (DisplayName = "Server Authorized"))
	bool ServerAuthorized();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Net Slime", Meta = (DisplayName = "Is Owning Client"))
	bool IsOwningClient();

	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (DisplayName = "NetLogA"))
	void Log(FString _message);

	// Has access to server RPCs. Does not care if your not the owner.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Server Authorized", ExpandEnumAsExecs = "ExecRoute"))
	void K2_ServerAuthorized(EIsResult &ExecRoute);

	// Has access to server RPCs, and is the designated client responsible for the actor.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Is Owning Client", ExpandEnumAsExecs = "ExecRoute"))
	void K2_IsOwningClient(EIsResult& ExecRoute);
};



// Interface
// If you need to deal with a large set of objects and have access to net slime actor info generically.

UINTERFACE(MinimalAPI)
class UNetSlimeActor : public UInterface
{
	GENERATED_BODY()

};

class NETWORKINGTEMPLATE_API INetSlimeActor
{
	GENERATED_BODY()

public:

	virtual bool ServerAuthorized()                 = NULL;
	virtual bool IsOwningClient  ()                 = NULL;
	virtual void NetLogA         (FString _message) = NULL;
};



// Quick way to generate functions for anything that wants easy non actor component access to netSlime actor info.
#define INetSlimeActor_Generate_Header() \
FORCEINLINE bool ServerAuthorized()                 { return UNetSlime_Actor::ServerAuthorized_Static(this);           } \
FORCEINLINE bool IsOwningClient  ()                 { return UNetSlime_Actor::IsOwningClient_Static  (this);           } \
FORCEINLINE void NetLogA         (FString _message) { return UNetSlime_Actor::Log_Static             (this, _message); }
