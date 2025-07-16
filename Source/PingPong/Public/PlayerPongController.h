#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPongController.generated.h"

UCLASS()
class PINGPONG_API APlayerPongController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(Server, Reliable, BlueprintCallable)
    void Server_RequestJoinMatch();

    UFUNCTION(Client, Reliable)
    void Client_ShowWaitingMessage();

    UFUNCTION(Client, Reliable)
    void Client_StartMatch();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
    TSubclassOf<UUserWidget> ScoreUIClass;

private:
    UPROPERTY()
    UUserWidget* MainMenuWidget;

    UPROPERTY(EditAnywhere, Category="UI")
    TSubclassOf<UUserWidget> MainMenuClass;

    UPROPERTY()
    UUserWidget* ScoreUIInstance;
};