// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// Unreal
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// UHeader Tool
#include "UStatic_Util.generated.h"



// Enum

UENUM(BlueprintType)
enum class EContinue : uint8
{
	Continue,
	_
};

UENUM(BlueprintType)
enum class EIsResult : uint8
{
	Yes,
	No
};



/**
 *
 */
UCLASS(Blueprintable)
class NETWORKINGTEMPLATE_API UStatic_Util : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

};