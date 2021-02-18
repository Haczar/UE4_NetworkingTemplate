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
class NETWORKINGTEMPLATE_API ANT_Character : public ACharacter, public INetSlime
{
	GENERATED_BODY()

public:

	INetSlime_Generate_Header();


	// Sets default values for this character's properties
	ANT_Character();



// APawn
public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* _playerInputComponent) override;


// AActor
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float _deltaTime) override;
};
