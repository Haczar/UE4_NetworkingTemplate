// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "UI_WidgetActorInterface_Base.h"



// Public

// Sets default values
AUI_WidgetActorInterface_Base::AUI_WidgetActorInterface_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// AActor

// Protected

// Called when the game starts or when spawned
void AUI_WidgetActorInterface_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Public

// Called every frame
void AUI_WidgetActorInterface_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

