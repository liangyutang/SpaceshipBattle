// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemySpawner.h"
#include "SpaceShip.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpaceshipBattle/SpaceshipBattleGameModeBase.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(RootComponent);

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>("ShipSM");
	ShipSM->SetupAttachment(CollisionComponent);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(this, 0));
	SetColor();

	//获取游戏模式
	MyGameMode= Cast<ASpaceshipBattleGameModeBase>( UGameplayStatics::GetGameMode(this));

	//获取Enemy生成器
	TArray<AActor*> EnemySpawnerArray;
	UGameplayStatics::GetAllActorsOfClass(this, AEnemySpawner::StaticClass(), EnemySpawnerArray);
	EnemySpawner = Cast<AEnemySpawner>(EnemySpawnerArray[0]);

}

void AEnemy::MoveTowardsPlayer()
{
	//移动向量
	const FVector Direction=FVector((SpaceShip->GetActorLocation() - GetActorLocation()).GetSafeNormal());

	//移动
	AddActorWorldOffset(Direction*Speed*FApp::GetDeltaTime(), true);
	//旋转
	SetActorRotation( UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), SpaceShip->GetActorLocation()));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!SpaceShip->GetBDead())
	{
		MoveTowardsPlayer();
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnDeath()
{
	MyGameMode->IncreaseScore();

	EnemySpawner->DecreaseEnemyCount();

	Destroy();
}

