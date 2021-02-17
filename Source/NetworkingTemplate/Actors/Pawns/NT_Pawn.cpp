// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "Actors/Pawns/NT_Pawn.h"


// Public

// Sets default values
ANT_Pawn::ANT_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}



// APawn

// Called to bind functionality to input
void ANT_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



// AActor

// Called when the game starts or when spawned
void ANT_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANT_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


