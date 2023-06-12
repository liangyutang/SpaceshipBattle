// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
	CollisionComponent->SetupAttachment(RootComponent);

	ShipSM = CreateDefaultSubobject<UStaticMeshComponent>("ShipSM");
	ShipSM->SetupAttachment(CollisionComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(ShipSM);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpawnPoint = CreateDefaultSubobject<USceneComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(ShipSM);

	Speed = 2500.f;

	TimeBetweenShot = 0.2f;

	bIsDead = false;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	//显示鼠标
	PC->bShowMouseCursor = true;
}

void ASpaceShip::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		//销毁
		Enemy->Destroy();
		//Destroy();
		OnDeath();
	}
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsDead)
	{
		LookAtCursor();

		Move(DeltaTime);
	}

	
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (const APlayerController* PlayerController=CastChecked<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Move, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Up)
		{
			EnhancedInputComponent->BindAction(IA_Up, ETriggerEvent::Triggered, this, &ASpaceShip::MoveUp);
		}

		if (IA_Right)
		{
			EnhancedInputComponent->BindAction(IA_Right, ETriggerEvent::Triggered, this, &ASpaceShip::MoveRight);
		}

		if (IA_Fire)
		{
			EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Started, this, &ASpaceShip::StartFire);
			EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Completed, this, &ASpaceShip::EndFire);
		}
	}


	
}

void ASpaceShip::Move(float DeltaTime)
{
	//FApp::GetDeltaTime();
	AddActorWorldOffset(ConsumeMovementInputVector()* Speed*DeltaTime,true) ;
}

void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;
    PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	const FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, GetActorLocation().Z);
	//飞机看向鼠标的角度
	const FRotator NowRotatory= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	SetActorRotation(NowRotatory);
}

void ASpaceShip::MoveUp(const FInputActionValue& InputValue)
{
	const float Value = InputValue.GetMagnitude();
	AddMovementInput(FVector::ForwardVector,Value);
}

void ASpaceShip::MoveRight(const FInputActionValue& InputValue)
{
	const float Value = InputValue.GetMagnitude();
	AddMovementInput(FVector::RightVector,Value);
}

void ASpaceShip::Fire()
{
	FActorSpawnParameters SpawnParameters;

	if (Bullet&&!bIsDead)
	{
		GetWorld()->SpawnActor<ABullet>(Bullet, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation(), SpawnParameters);

		UGameplayStatics::PlaySoundAtLocation(this, ShootCue, GetActorLocation());
	}
}

void ASpaceShip::StartFire()
{

	GetWorldTimerManager().SetTimer(TimerHandle_BetweenShot, this, &ASpaceShip::Fire, TimeBetweenShot, true, 0.0f);
}

void ASpaceShip::EndFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_BetweenShot);
}

void ASpaceShip::ReStartLevel()
{
	
	UGameplayStatics::OpenLevel(this, "MainMap");
}

void ASpaceShip::OnDeath()
{

	CollisionComponent->SetVisibility(false,true);

	bIsDead = true;

	//播放死亡音乐
	UGameplayStatics::PlaySoundAtLocation(this, GameOverCue, GetActorLocation());

	GetWorldTimerManager().SetTimer(TimerHandle_RestartGame, this,&ASpaceShip::ReStartLevel, 2.0f,false);
}


