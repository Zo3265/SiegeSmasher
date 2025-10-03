// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"
#include "EnemyInheritTest.generated.h"

UCLASS()
class SIEGESMASHER_API AEnemyInheritTest : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyInheritTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int CalculateWaveContribution(float FractionalWaveNumber);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
