// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class SPACESHIPBATTLE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetColor();

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* ShipSM;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* CollisionComponent;

	UPROPERTY()
	class ASpaceShip* SpaceShip;

	float Speed = 300.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveTowardsPlayer();


};
