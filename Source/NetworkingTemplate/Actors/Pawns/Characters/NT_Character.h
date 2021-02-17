// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// NetSlime
#include "NetSlime/NetSlime_Static.h"
#include "NetSlime/NetSlime_Actor.h"

// UE Header Tool
#include "NT_Character.generated.h"



UCLASS()
class NETWORKINGTEMPLATE_API ANT_Character : public ACharacter, public INetSlime, public INetSlimeActor
{
	GENERATED_BODY()

public:

	INetSlime_Generate_Header();
	
	INetSlimeActor_Generate_Header();

	// Non-Macroable.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "ServerAuthorized", ExpandEnumAsExecs = "ExecRoute"))
	void K2_ServerAuthorized(EIsResult& ExecRoute) { if (ServerAuthorized()) 
	{ ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "IsOwningClient", ExpandEnumAsExecs = "ExecRoute"))
	void K2_IsOwningClient  (EIsResult& ExecRoute) { if (IsOwningClient  ()) 
	{ ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }



	// Sets default values for this character's properties
	ANT_Character();



// APawn
public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


// AActor
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
