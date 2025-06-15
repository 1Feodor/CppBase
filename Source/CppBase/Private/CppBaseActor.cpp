// Fill out your copyright notice in the Description page of Project Settings.


#include "CppBaseActor.h"
#include "Engine/Engine.h"
#include "Math/UnrealMathUtility.h"

int ACppBaseActor::Id = 0 ;
// Sets default values
ACppBaseActor::ACppBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject< UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
}

// Called when the game starts or when spawned
void ACppBaseActor::BeginPlay()
{
	Super::BeginPlay();
	ShowActorInformation();
	this->InitialLocation = GetActorLocation() + FVector(0.0f, 0.0f, this->Amplitude);
}

// Called every frame
void ACppBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACppBaseActor::ShowInformation()
{
	UE_LOG(LogTemp, Display, TEXT("CppBase is here!"));
	UE_LOG(LogTemp, Warning, TEXT("CppBase класс ошибся!"));
	UE_LOG(LogTemp, Error, TEXT("CppBase Ошибка!!!"));

	UE_LOG(LogTemp, Display, L"fff");
	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("CurrentHealth: %f"), CurrentHealth);
	UE_LOG(LogTemp, Display, TEXT("IsAlive: %i"), IsAlive);
	
	UE_LOG(LogTemp, Display, TEXT("PlauerName: %s"), *PlauerName);

	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, PlauerName, true, FVector2D(2.0f, 2.0f));
}

void ACppBaseActor::SinMovement()
{
	SetActorLocation(FVector(this->InitialLocation.X, this->InitialLocation.Y, 
	FMath::Sin(this->Frequency * (GetWorld()->GetTimeSeconds() + this->EnemyNum)) * this->Amplitude
	+ this->InitialLocation.Z));
}

void ACppBaseActor::ShowActorInformation()
{
	this->PlauerName += FString::Printf(TEXT("_%d"), Id);
	this->IsAlive = static_cast<bool>(Id % 2);
	++this->Id;
	this->EnemyNum = this->Id * 10;

	UE_LOG(LogTemp, Display, TEXT("Instance name: %s"), *PlauerName);
	UE_LOG(LogTemp, Display, TEXT("EnemyNum: %d"), EnemyNum);
	UE_LOG(LogTemp, Display, TEXT("IsAlive: %i"), IsAlive);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, PlauerName, true, FVector2D(2.0f, 2.0f));
}

