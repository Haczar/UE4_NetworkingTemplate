// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UStatic_Util.h"

// NT
#include "NT_PlayerState.h"


// NetSlime
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
class NETWORKINGTEMPLATE_API ANT_PlayerController : public APlayerController, public INetSlime
{
	GENERATED_BODY()

public:

	// Net Slime.

	INetSlime_Generate_Header();


	ANT_PlayerController();

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Owning Client: Post Login"))
	FDelegate_OwningClient_PostLoginReady On_OwningClient_PostLogin;

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Pawn: Possessed"))
	FDelegate_PawnPossessed On_PawnPossessed;

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Player: Ready"))
	FDelegate_PlayerReady On_OwningClient_Ready;

protected:

	friend void ANT_PlayerState::ClientInitialize(class AController* _newOwner);

	UFUNCTION()
	virtual void Local_FrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local: On Framework Initialized"))
	void K2_Local_FrameworkInitialized();

	UFUNCTION()
	virtual void PawnReady();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Pawn Ready"))
	void K2_PawnReady();

	void Client_ProcessPlayerState();

	// This is the safest place to do all the starting logic as all possible setup, replication and referencing desired should have been finished.
	UFUNCTION()
	virtual void OwningClient_Ready();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Owning Client: Ready"))
	void K2_OwningClient_Ready();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyOwningClient_Ready();

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
