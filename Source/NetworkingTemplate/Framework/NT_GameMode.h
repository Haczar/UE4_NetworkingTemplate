// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

// NT 
//#include "NT_GameInstance.h"


// UE Header Tool
#include "NT_GameMode.generated.h"



// Pawn.h
class APawn;



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_GameMode : public AGameMode	
{
	GENERATED_BODY()

public:

	

protected:

	UFUNCTION()
	void Server_On_OwningClient_PostLogin(ANT_PlayerController* _player);

	UFUNCTION()
	void Server_OnFrameworkInitialized();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Sever_On_FrameworkInitialized"))
	void K2_Server_OnFrameworkInitialized(); 

private:

	
// AGameMode

protected:

	virtual bool ReadyToStartMatch_Implementation() override;


// AGameModeBase

protected:

	virtual void StartPlay() override;

	virtual void PostLogin(APlayerController* NewPlayer) override;
};


