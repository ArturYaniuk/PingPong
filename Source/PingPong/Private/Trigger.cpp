// Fill out your copyright notice in the Description page of Project Settings.


#include "PingPong/Public/Trigger.h"

#include "BallActor.h"
#include "GamePongModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATrigger::ATrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("CollisionBox"));
	RootComponent = CollisionBox;

	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	CollisionBox->SetGenerateOverlapEvents(true);
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
	if (ABallActor* Ball = Cast<ABallActor>(OtherActor))
	{
		AGamePongModeBase* GM = Cast<AGamePongModeBase>(UGameplayStatics::GetGameMode(this));
		if (GM)
		{
			GM->AddScore(PlayerIndex);

			OtherActor->Destroy();

			GM->SpawnNewBall();
		}
	}
}

// Called every frame
void ATrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

