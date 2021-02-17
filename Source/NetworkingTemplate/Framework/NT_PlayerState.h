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
	
};
