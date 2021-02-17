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

	bool ServerAuthorized();
	bool IsOwningClient();

	// Has access to server RPCs. Does not care if your not the owner.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "ServerAuthorized", ExpandEnumAsExecs = "ExecRoute"))
	void K2_ServerAuthorized(EIsResult &ExecRoute);

	// Has access to server RPCs, and is the designated client responsible for the actor.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "IsOwningClient", ExpandEnumAsExecs = "ExecRoute"))
	void K2_IsOwningClient(EIsResult& ExecRoute);
};



// Interface

UINTERFACE(MinimalAPI)
class UNetSlimeActor : public UInterface
{
	GENERATED_BODY()

};

class NETWORKINGTEMPLATE_API INetSlimeActor
{
	GENERATED_BODY()

public:

	virtual bool ServerAuthorized() = NULL;
	virtual bool IsOwningClient  () = NULL;
};

#define INetSlimeActor_Generate_Header() \
FORCEINLINE bool ServerAuthorized() { return UNetSlime_Actor::ServerAuthorized_Static(this); } \
FORCEINLINE bool IsOwningClient  () { return UNetSlime_Actor::IsOwningClient_Static  (this); } 