#pragma once

// Unreal
#include "CoreMinimal.h"

// Networking
#include "Engine/NetworkDelegates.h"
#include "Net/UnrealNetwork.h"
#include "Net/RepLayout.h"


// UE Header Tool
#include "NT_Framework.generated.h"



UENUM(BlueprintType)
enum class EFramework_ComponentFlag : uint8
{
	None             = 0 UMETA(Hidden),
	GameMode         = 1 << 0,
	GameState        = 1 << 1,
	PlayerController = 1 << 2,
	PlayerState      = 1 << 3,
	Levels           = 1 << 4
};

UENUM(BlueprintType)
enum class EFramework_State : uint8
{
	Initialized,
	Uninitialized
};
