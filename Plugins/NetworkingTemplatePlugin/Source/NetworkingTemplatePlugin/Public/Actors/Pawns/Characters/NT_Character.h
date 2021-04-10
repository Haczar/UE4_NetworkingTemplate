// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// NetSlime
#include "NetSlime_Static.h"

// NT
#include "Pawns/NT_Pawn.h"

// UE Header Tool
#include "NT_Character.generated.h"



UCLASS()
class NETWORKINGTEMPLATEPLUGIN_API ANT_Character : public ACharacter, public INetSlime
{
	GENERATED_BODY()

public:

	INetSlime_Generate_Header();


	// Sets default values for this character's properties
	ANT_Character();

	UFUNCTION()
	virtual void Controller_PawnPossessed();

	UFUNCTION(Category = "Framework", BlueprintCallable, BlueprintImplementableEvent, meta = (DisplayName = "Controller: Pawn Possessed"))
	void K2_Controller_PawnPossessed();

	UFUNCTION(Server, Reliable)
	void ServerRPC_Reliable_NotifyClientPawnReady();

	UPROPERTY(Category = "Framework", BlueprintAssignable, BlueprintCallable, Meta = (DisplayName = "On Pawn: Ready"))
	FDelegate_PawnReady On_PawnReady;


// APawn
public:

	virtual void PossessedBy(AController* _newController) override;

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
