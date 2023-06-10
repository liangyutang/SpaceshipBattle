// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	

}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<APlayerController>(GetController());
	//显示鼠标
	PC->bShowMouseCursor = true;
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtCursor();
}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASpaceShip::LookAtCursor()
{
	FVector MouseLocation, MouseDirection;
    PC->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

	FVector TargetLocation = FVector(MouseLocation.X, MouseLocation.Y, 0);
	//飞机看向鼠标的角度
	const FRotator NowRotatory= UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);

	SetActorRotation(NowRotatory);
}

void ASpaceShip::MoveUp(float Value)
{
	AddMovementInput(FVector::UpVector,Value);
}

void ASpaceShip::MoveRight(float Value)
{
	AddMovementInput(FVector::RightVector,Value);
}


