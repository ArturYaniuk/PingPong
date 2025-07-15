#include "GamePongModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

void AGamePongModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    if (GetNumPlayers() == 2)
    {
        UE_LOG(LogTemp, Warning, TEXT("Second player joined, starting match!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Waiting for another player..."));
    }
}