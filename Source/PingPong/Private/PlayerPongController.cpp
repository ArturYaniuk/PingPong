#include "PlayerPongController.h"

void APlayerPongController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController())
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Controller ready"));
    }
}