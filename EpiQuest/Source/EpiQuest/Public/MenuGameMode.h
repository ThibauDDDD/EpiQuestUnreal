#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuPlayerController.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h" 
#include "Blueprint/UserWidget.h"

#include "MenuGameMode.generated.h"

class UUserWidget;

UCLASS()
class EPIQUEST_API AMenuGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMenuGameMode();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    USoundWave* CurrentMenuMusic;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> CurrentMenuWidgetClass;

    UPROPERTY()
    UUserWidget* CurrentWidget;

protected:
    virtual void BeginPlay() override;
};
