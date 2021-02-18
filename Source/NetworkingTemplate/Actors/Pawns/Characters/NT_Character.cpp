// Fill out your copyright notice in the Description page of Project Settings.

// Parent
#include "Actors/Pawns/Characters/NT_Character.h"



// Sets default values
ANT_Character::ANT_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANT_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANT_Character::Tick(float _deltaTime)
{
	Super::Tick(_deltaTime);

}

// Called to bind functionality to input
void ANT_Character::SetupPlayerInputComponent(UInputComponent* _playerInputComponent)
{
	Super::SetupPlayerInputComponent(_playerInputComponent);

}

