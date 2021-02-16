// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_GameInstance.h"

// Unreal
//#include "GameplayStatics.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Bitmask/Bitmask_Util.h"



// Public

bool UNT_GameInstance::Local_IsFrameworkInitialized() const
{
	return frameworkState == EFramework_State::Initialized;
}

void UNT_GameInstance::Local_NotifyComponentReady(EFramework_ComponentFlag _componentReady)
{
	switch (_componentReady)
	{
		case EFramework_ComponentFlag::GameMode:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::GameMode;

			UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework component ready: Game Mode."));

			break;
		}
		case EFramework_ComponentFlag::GameState:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::GameState;

			UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework component ready: Game State."));

			break;
		}
		case EFramework_ComponentFlag::PlayerController:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::PlayerController;

			UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework component ready: Player Controller."));

			break;
		}
		case EFramework_ComponentFlag::PlayerState:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::PlayerState;

			UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework component ready: Player State."));

			break;
		}
		case EFramework_ComponentFlag::Levels:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::Levels;

			UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework component ready: Levels."));

			break;
		}
	}

	Local_ProcessFrameworkState();
}



// Protected

void UNT_GameInstance::Local_ClearFrameworkState()
{
	UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Clearing framework state."));

	frameworkComponentState = int32(EFramework_ComponentFlag::None);
	frameworkState          = EFramework_State::Uninitialized;
}



void UNT_GameInstance::Local_ProcessFrameworkState()
{
	switch (frameworkState)
	{
		case EFramework_State::Uninitialized:
		{
			uint32 initalizedFlags =
				(uint32)EFramework_ComponentFlag::GameState        |
				(uint32)EFramework_ComponentFlag::PlayerController |
				(uint32)EFramework_ComponentFlag::PlayerState      |
				(uint32)EFramework_ComponentFlag::Levels
			;

			if (GetWorld()->IsServer())
			{
				initalizedFlags |= (uint32)EFramework_ComponentFlag::GameMode;
			}

			if (UBitmask_Util::IsEqual_Pure(frameworkComponentState, initalizedFlags))
			{
				frameworkState = EFramework_State::Initialized;

				UE_LOG(LogTemp, Log, TEXT("NT_GameInstance: Framework initalized."));

				Framework_Initialized.Broadcast();
			}

			break;
		}
	}
}

ANT_PlayerController* UNT_GameInstance::Local_GetInstanceUser()
{
	return Cast<ANT_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
