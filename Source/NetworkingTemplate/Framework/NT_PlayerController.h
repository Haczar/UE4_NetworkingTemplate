// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UStatic_Util.h"
#include "NetSlime/NetSlime_Static.h"
#include "NetSlime/NetSlime_Actor.h"

// UE Header Tool
#include "NT_PlayerController.generated.h"


// Forwards

class UNT_GameInstance;
class ANT_PlayerController;
class ANT_GameMode;
class UNetSlime;


// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_OwningClient_PostLoginReady, ANT_PlayerController*, _player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_PawnPossessed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_PlayerReady);


/**
 * 
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_PlayerController : public APlayerController, public INetSlime, public INetSlimeActor
{
	GENERATED_BODY()

public:

	// Net Slime.

	INetSlime_Generate_Header();

	INetSlimeActor_Generate_Header();

	// Non-Macroable.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Server Authorized", ExpandEnumAsExecs = "ExecRoute"))
	void K2_ServerAuthorized(EIsResult& ExecRoute) 
	{ if (ServerAuthorized()) { ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "Is Owning Client", ExpandEnumAsExecs = "ExecRoute"))
	void K2_IsOwningClient  (EIsResult& ExecRoute) 
	{ if (IsOwningClient  ()) { ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }


	ANT_PlayerController();

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Owning Client: Post Login"))
	FDelegate_OwningClient_PostLoginReady On_OwningClient_PostLogin;

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Pawn: Possessed"))
	FDelegate_PawnPossessed On_PawnPossessed;

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Player: Ready"))
	FDelegate_PlayerReady On_PlayerReady;

protected:

	UFUNCTION()
	virtual void Local_OnFrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local: On FrameworkInitialized"))
	void K2_Local_OnFrameworkInitialized();

	UFUNCTION()
	virtual void OnPawnReady();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "On Pawn Ready"))
	void K2_OnPawnReady();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyClientPlayerReady();

	UFUNCTION()
	void Server_SetOwningClient_FrameworkInitialized();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient();

	UPROPERTY(Category = "Framework", Replicated, VisibleAnywhere, Meta = (DisplayName = "On Owning Client: Framework Initialized"))
	bool bOwningClient_FrameworkInitialized = false;

private:

	
	
		
// APlayerController
public:

	virtual bool CanRestartPlayer() override;

// AController

	virtual void OnPossess(APawn* aPawn) override;

// AActor
public:

	virtual void BeginPlay() override;
};
