// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

// NT 
#include "NetSlime/NetSlime_Static.h"


// UE Header Tool
#include "NT_GameMode.generated.h"



// Pawn.h
class APawn;



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_GameMode : public AGameMode, public INetSlime	
{
	GENERATED_BODY()

public:

	INetSlime_Generate_Header();


	ANT_GameMode();

protected:

	UFUNCTION()
	void Server_OwningClient_PostLogin(ANT_PlayerController* _player);

	UFUNCTION()
	void Server_FrameworkInitialized();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Sever_On_Framework Initialized"))
	void K2_Server_FrameworkInitialized(); 

private:

	
// AGameMode

protected:

	virtual bool ReadyToStartMatch_Implementation() override;


// AGameModeBase

protected:

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};


