// We need to see a lawyer.

#pragma once

// Include

// Unreal
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Phantom
#include "Utilities/UStatic_Util.h"

// UE Header Tool
#include "NetSlime_ActorComponent.generated.h"



// Look into make a net slime actor class as well.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NETWORKINGTEMPLATE_API UNetSlime_ActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetSlime_ActorComponent();

	bool IsOwningClient_Pure();

	// Has access to server RPCs. Does not care if your not the owner.
	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		void ServerAuthorized(UObject* WorldContextObject, EIsResult &ExecRoute);

	// Has access to server RPCs, and is the designated client responsible for the actor.
	UFUNCTION(BlueprintCallable, Category = "Net Slime", Meta = (CallableWithoutWorldContext, ExpandEnumAsExecs = "ExecRoute", WorldContext = "WorldContextObject"))
		void IsOwningClient(UObject* WorldContextObject, EIsResult& ExecRoute);

protected:
	// Called when the game starts
	//virtual void BeginPlay() override;
	
};
