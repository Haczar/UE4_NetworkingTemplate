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

	ANT_PlayerController();

	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite)
	FDelegate_OwningClient_PostLoginReady On_OwningClient_PostLogin;

protected:

	UFUNCTION()
	virtual void Local_OnFrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local_On_FrameworkInitialized"))
	void K2_Local_OnFrameworkInitialized();

	UFUNCTION()
	void Server_SetOwningClient_FrameworkInitialized();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient();

	UPROPERTY(Category = "Framework", Replicated, BlueprintReadOnly, VisibleAnywhere) 
	bool bOwningClient_FrameworkInitialized = false;

private:

	
	
		
// APlayerController
public:

	virtual bool CanRestartPlayer() override;

// AController

	//virtual void OnPossess(APawn* aPawn) override;

// AActor
public:

	virtual void BeginPlay() override;
};
