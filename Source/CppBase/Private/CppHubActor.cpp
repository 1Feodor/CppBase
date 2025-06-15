// Fill out your copyright notice in the Description page of Project Settings.


#include "CppHubActor.h"
#include "TimerManager.h"
#include "CppBaseActor.h"

// Sets default values
ACppHubActor::ACppHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACppHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(this->SpawnTimerHandle, this, &ACppHubActor::OnTimeToSpawn, this->SpawnTimerRate, true);
	UE_LOG(LogTemp, Display, TEXT("CppBase is here!"));
}

void ACppHubActor::OnTimeToSpawn()
{
	if (++this->CurrentTimerCount <= this->TotalCount)
	{
		const FVector Location = GetActorLocation() + FVector(FMath::FRandRange(200.0f, 1000.0f), FMath::FRandRange(200.0f, 1000.0f), 0.0f);
		const FRotator Rotation = FRotator::ZeroRotator;
		ACppBaseActor* SpawnObject = GetWorld()->SpawnActor<ACppBaseActor>(CppClass, Location, Rotation);
		if (SpawnObject)
		{
			SpawnedObjects.Add(SpawnObject);
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(this->SpawnTimerHandle);
		for (int i = this->TotalCount; i >= 1; --i)
		{
			GetWorldTimerManager().SetTimer(this->DestroyTimerHandle, this, &ACppHubActor::OnTimeToDestroy, this->DestroyTimerRate, true);
		}
	}
}

void ACppHubActor::OnTimeToDestroy()
{
	if (!SpawnedObjects.IsEmpty())
	{
		SpawnedObjects.Top()->Destroy();
		SpawnedObjects.Pop();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(this->DestroyTimerHandle);
		this->CurrentTimerCount = 0;
		GetWorldTimerManager().SetTimer(this->SpawnTimerHandle, this, &ACppHubActor::OnTimeToSpawn, this->SpawnTimerRate, true);
	}
}


// Called every frame
void ACppHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

