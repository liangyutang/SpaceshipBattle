





// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Enemy.h"
#include "Engine/BlockingVolume.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComp->SetupAttachment(RootComponent);

	BulletSM = CreateDefaultSubobject<UStaticMeshComponent>("BulletSM");
	BulletSM->SetupAttachment(RootComp);

	//�ӵ��������
	ProjectileMoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AEnemy *Enemy =Cast<AEnemy>(OtherActor))
	{
		UE_LOG(LogTemp, Error, TEXT("1"));

		//����
		Enemy->Destroy();
		Destroy();
	}

	//����ǽ������
	if (Cast<ABlockingVolume>(OtherActor))
	{
		Destroy();
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

