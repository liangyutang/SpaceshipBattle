// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class SPACESHIPBATTLE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

	FTimerHandle TimerHandle_Spawn;

	UPROPERTY(EditAnywhere,Category="Spwan")
	float SpawnInterval=2;

protected:
	UPROPERTY(EditAnywhere,Category="Enemy")
	TSubclassOf<class AEnemy> Enemy;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	class UBoxComponent* SpawnArea;

	UPROPERTY()
	class ASpaceShip* SpaceShip;

	float MinimumDistanceToPlayer = 1200.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief 寻找敌人可生成的位置
	 * @return 敌人生成的位置
	 */
	FVector GetGenerateLocation();

	void SpawnEnemy();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
