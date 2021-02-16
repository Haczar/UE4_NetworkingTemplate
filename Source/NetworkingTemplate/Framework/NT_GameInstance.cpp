// Fill out your copyright notice in the Description page of Project Settings.


#include "NT_GameInstance.h"




// Protected

void UNT_GameInstance::ClearFrameworkState()
{
	UE_LOG(LogTemp, ELogVerbosity::Log, TEXT("NT_GameInstance: Clearing framework state."));

	frameworkComponentState = int32(EFramework_ComponentFlag::None);
	frameworkState          = EFramework_State::Uninitialized;
}
