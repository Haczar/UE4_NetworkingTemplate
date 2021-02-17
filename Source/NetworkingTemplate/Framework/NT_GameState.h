// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"

// NetSlime
#include "NetSlime/NetSlime_Static.h"

// UE Header Tool
#include "NT_GameState.generated.h"



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_GameState : public AGameState, public INetSlime
{
	GENERATED_BODY()
	
public:

	INetSlime_Generate_Header();

	ANT_GameState();


protected:

	UFUNCTION()
	virtual void Local_FrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local: Framework Initialized"))
	void K2_Local_FrameworkInitialized();


	// AGameState

public:

	// AActor

public:

	virtual void BeginPlay() override;


};
