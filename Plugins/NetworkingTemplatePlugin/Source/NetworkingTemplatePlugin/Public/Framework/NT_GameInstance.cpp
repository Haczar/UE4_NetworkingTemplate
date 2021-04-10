// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "NT_GameInstance.h"

// Unreal
//#include "GameplayStatics.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "Bitmask_Util.h"
#include "NT_PlayerController.h"



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

			NetLog(TEXT("Framework component ready: Game Mode."));

			break;
		}
		case EFramework_ComponentFlag::GameState:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::GameState;

			NetLog(TEXT("Framework component ready: Game State."));

			break;
		}
		case EFramework_ComponentFlag::PlayerController:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::PlayerController;

			NetLog(TEXT("Framework component ready: Player Controller."));

			break;
		}
		case EFramework_ComponentFlag::PlayerState:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::PlayerState;

			NetLog(TEXT("Framework component ready: Player State."));

			break;
		}
		case EFramework_ComponentFlag::Levels:
		{
			frameworkComponentState |= (uint32)EFramework_ComponentFlag::Levels;

			NetLog(TEXT("Framework component ready: Levels."));

			break;
		}
	}

	Local_ProcessFrameworkState();
}



// Protected

void UNT_GameInstance::Local_ClearFrameworkState()
{
	NetLog(TEXT("Clearing framework state."));

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

				NetLog(TEXT("Framework initialized."));

				On_Framework_Initialized.Broadcast();
			}

			break;
		}
	}
}

ANT_PlayerController* UNT_GameInstance::Local_GetInstanceUser()
{
	return Cast<ANT_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

