// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "Actors/NT_Actor.h"



// Sets default values
ANT_Actor::ANT_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANT_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANT_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

