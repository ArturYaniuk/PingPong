#include "PlayerPongController.h"

#include "GamePongModeBase.h"
#include "Blueprint/UserWidget.h"

void APlayerPongController::BeginPlay()
{
    Super::BeginPlay();

    if (IsLocalController() && MainMenuClass)
    {
        MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();
            SetShowMouseCursor(true);

            FInputModeUIOnly InputMode;
            InputMode.SetWidgetToFocus(MainMenuWidget->TakeWidget());
            SetInputMode(InputMode);
        }
    }
    if (IsLocalController() && ScoreUIClass)
    {
        ScoreUIInstance = CreateWidget<UUserWidget>(this, ScoreUIClass);
        if (ScoreUIInstance)
        {
            ScoreUIInstance->AddToViewport();
        }
    }
}

void APlayerPongController::Client_StartMatch_Implementation()
{
    if (MainMenuWidget)
    {
        MainMenuWidget->RemoveFromParent();
    }
    SetShowMouseCursor(false);

    FInputModeGameOnly InputMode;
    SetInputMode(InputMode);
}

void APlayerPongController::Client_ShowWaitingMessage_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Waiting for another player..."));
}

void APlayerPongController::Server_RequestJoinMatch_Implementation()
{
    AGamePongModeBase* GM = Cast<AGamePongModeBase>(GetWorld()->GetAuthGameMode());
    if (GM)
    {
        GM->TryStartMatch(this);
    }
}
