// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPACESHIPBATTLE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere,Category="Component")
	UStaticMeshComponent* BulletSM;

	//�������
	UPROPERTY()
	class UProjectileMovementComponent* ProjectileMoveComp;

	UPROPERTY(BlueprintReadWrite)
	class AEnemySpawner* EnemySpawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
