// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "SpaceShip.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SpawnArea->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip= Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}

FVector AEnemySpawner::GetGenerateLocation()
{
	float Distance = 0;
	FVector FindLocation;
	while (Distance<MinimumDistanceToPlayer)
	{
		FindLocation = UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);

		Distance = (FindLocation - SpaceShip->GetActorLocation()).Size();
	}

	return FindLocation;

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

