// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_GameState.h"


// NT
#include "NT_GameInstance.h"



// Public

ANT_GameState::ANT_GameState()
{

}


// Protected 

void ANT_GameState::Local_FrameworkInitialized()
{
	NetLog(TEXT("Received framework initialization."));

	K2_Local_FrameworkInitialized();
}



// AActor

// Public

void ANT_GameState::BeginPlay()
{
	Super::BeginPlay();

	NetLog(TEXT("Begin Play called."));

	UNT_GameInstance* gInst = GetGameInstance<UNT_GameInstance>();

	gInst->On_Framework_Initialized.AddDynamic(this, &ANT_GameState::Local_FrameworkInitialized);

	gInst->Local_NotifyComponentReady(EFramework_ComponentFlag::GameState);
}
