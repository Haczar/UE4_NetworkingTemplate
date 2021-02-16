// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// NT
#include "NT_Framework.h"
#include "NT_PlayerController.h"

// UE Header Tool
#include "NT_GameInstance.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegate_FrameworkInitialized);



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API UNT_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintPure)
	bool Local_IsFrameworkInitialized() const;

	UFUNCTION(Category = "Framework", BlueprintCallable)
	void Local_NotifyComponentReady(EFramework_ComponentFlag _componentReady);

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable)
	FDelegate_FrameworkInitialized Framework_Initialized;

protected:

	UFUNCTION(Category = "Framework", BlueprintCallable, meta = (BlueprintProtected))
	void Local_ClearFrameworkState();
	
	UFUNCTION(Category = "Framework", BlueprintCallable, meta = (BlueprintProtected))
	void Local_ProcessFrameworkState();

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected), BlueprintPure)
	ANT_PlayerController* Local_GetInstanceUser();



	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = EFramework_ComponentFlag))
	int32 frameworkComponentState = 0;

	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite)
	EFramework_State frameworkState = EFramework_State::Uninitialized;
};
