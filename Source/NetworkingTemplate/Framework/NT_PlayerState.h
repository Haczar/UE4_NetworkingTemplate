// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"

// NetSlime
#include "NetSlime/NetSlime_Static.h"

// UE Header Tool
#include "NT_PlayerState.generated.h"



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_PlayerState : public APlayerState, public INetSlime
{
	GENERATED_BODY()

public:

	INetSlime_Generate_Header();


	ANT_PlayerState();

protected:

	UFUNCTION()
	virtual void Local_FrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local: Framework Initialized"))
	void K2_Local_FrameworkInitialized();



// APlayerState

public:


// AActor

public:

	virtual void BeginPlay() override;

	// This gets called on replication of the player state (client side only).
	virtual void ClientInitialize(class AController* _newOwner) override;

	virtual void PostInitializeComponents() override;

	virtual void Reset() override;
};
