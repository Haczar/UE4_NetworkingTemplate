// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"



#include "NT_PlayerController.generated.h"

// NT_GameInstance.h
class UNT_GameInstance;
class ANT_PlayerController;
class ANT_GameMode;
class UNetSlime_ActorComponent;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegate_OwningClient_PostLoginReady, ANT_PlayerController*, _player);



/**
 * 
 */
UCLASS()
class NETWORKINGTEMPLATE_API ANT_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ANT_PlayerController();

	UPROPERTY(Category = "Framework", EditAnywhere, BlueprintReadWrite)
	FDelegate_OwningClient_PostLoginReady On_OwningClient_PostLogin;

protected:

	UFUNCTION()
	virtual void Local_OnFrameworkInitialized();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Local_On_FrameworkInitialized"))
	void K2_Local_OnFrameworkInitialized();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UNetSlime_ActorComponent* netSlime;

	UFUNCTION()
	void Server_SetOwningClient_FrameworkInitialized();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyFrameworkInit_OnOwningClient();

	UPROPERTY(Category = "Framework", Replicated, BlueprintReadOnly, EditAnywhere)
	bool bOwningClient_FrameworkInitialized = false;

private:

	
		
// APlayerController
public:

	virtual void BeginPlay() override;

	virtual bool CanRestartPlayer() override;
};
