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
};