// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// NetSlime
#include "NetSlime/NetSlime_Static.h"
#include "NetSlime/NetSlime_Actor.h"

// UE Header Tool
#include "NT_Actor.generated.h"



UCLASS()
class NETWORKINGTEMPLATE_API ANT_Actor : public AActor, public INetSlime, public INetSlimeActor
{
	GENERATED_BODY()
	
public:	

	// Net Slime

	INetSlime_Generate_Header();

	INetSlimeActor_Generate_Header();

	// Non-Macroable.
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "ServerAuthorized", ExpandEnumAsExecs = "ExecRoute"))
	void K2_ServerAuthorized(EIsResult& ExecRoute) 
	{ if (ServerAuthorized()) { ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }
	UFUNCTION(Category = "Net Slime", BlueprintCallable, Meta = (DisplayName = "IsOwningClient", ExpandEnumAsExecs = "ExecRoute"))
	void K2_IsOwningClient  (EIsResult& ExecRoute) 
	{ if (IsOwningClient  ()) { ExecRoute = EIsResult::Yes; return; } else { ExecRoute = EIsResult::No; return; } }


	// Sets default values for this actor's properties
	ANT_Actor();




	// AAActor

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
