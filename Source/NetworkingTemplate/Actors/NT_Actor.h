// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// NetSlime
#include "NetSlime/NetSlime_Static.h"

// UE Header Tool
#include "NT_Actor.generated.h"



UCLASS()
class NETWORKINGTEMPLATE_API ANT_Actor : public AActor, public INetSlime
{
	GENERATED_BODY()
	
public:	

	// Net Slime

	INetSlime_Generate_Header();


	// Sets default values for this actor's properties
	ANT_Actor();


	// AAActor

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float _deltaTime) override;
};
