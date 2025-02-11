#include "MenuGameMode.h"
#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"

AMenuGameMode::AMenuGameMode()
{
    //PlayerControllerClass = AMainMenuPlayerController::StaticClass();

    //DefaultPawnClass = nullptr;
}

void AMenuGameMode::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::PlaySound2D(GetWorld(), CurrentMenuMusic);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), CurrentMenuWidgetClass);
    
    CurrentWidget->AddToViewport();

    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;

        /*FInputModeUIOnly InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);*/
    }
}

