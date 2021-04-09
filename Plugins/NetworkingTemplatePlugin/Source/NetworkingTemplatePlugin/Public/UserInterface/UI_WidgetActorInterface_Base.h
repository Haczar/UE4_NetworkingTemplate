// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Unreal
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

// UHeader Tool
#include "UI_WidgetActorInterface_Base.generated.h"



UCLASS()
class NETWORKINGTEMPLATEPLUGIN_API AUI_WidgetActorInterface_Base : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AUI_WidgetActorInterface_Base();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
