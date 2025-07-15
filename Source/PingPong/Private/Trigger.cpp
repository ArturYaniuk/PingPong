// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/Public/Trigger.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATrigger::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATrigger::OnSphereOverlap);
}

void ATrigger::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATrigger::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

