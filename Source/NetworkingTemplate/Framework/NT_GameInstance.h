// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// NT
#include "NT_Framework.h"

// UE Header Tool
#include "NT_GameInstance.generated.h"



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API UNT_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	

protected:



	UFUNCTION(Category = "Framework", BlueprintCallable)
	void ClearFrameworkState();





	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EFramework_ComponentFlag))
	int32 frameworkComponentState;

	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite)
	EFramework_State frameworkState;
};
