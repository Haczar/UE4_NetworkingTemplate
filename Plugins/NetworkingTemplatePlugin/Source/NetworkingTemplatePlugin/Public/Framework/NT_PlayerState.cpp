// Fill out your copyright notice in the Description page of Project Settings.


// Parent
#include "NT_PlayerState.h"


#include "NT_GameInstance.h"
#include "NT_PlayerController.h"




// Public

ANT_PlayerState::ANT_PlayerState()
{

}


// Protected 

void ANT_PlayerState::Local_FrameworkInitialized()
{
	NetLog(TEXT("Received framework initialization."));

	K2_Local_FrameworkInitialized();
}


// APlayerState

// Public



// AActor

// Public

void ANT_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	NetLog(TEXT("Begin Play called."));

	UNT_GameInstance* gInst = GetGameInstance<UNT_GameInstance>();

	gInst->On_Framework_Initialized.AddDynamic(this, &ANT_PlayerState::Local_FrameworkInitialized);

	gInst->Local_NotifyComponentReady(EFramework_ComponentFlag::PlayerState);
}

void ANT_PlayerState::ClientInitialize(class AController* _newOwner)
{
	Super::ClientInitialize(_newOwner);

	NetLog(TEXT("Client Initialization."));

	ANT_PlayerController* ntController = Cast<ANT_PlayerController>(_newOwner);

	ntController->Client_ProcessPlayerState();
}

void ANT_PlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	NetLog(TEXT("Post Initialization."));
}

void ANT_PlayerState::Reset()
{
	Super::Reset();

	NetLog(TEXT("Reset."));
}
