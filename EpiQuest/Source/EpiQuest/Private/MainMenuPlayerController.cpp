#include "MainMenuPlayerController.h"

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    
    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    SetInputMode(InputMode);

    SetIgnoreMoveInput(true);
    SetIgnoreLookInput(true);
}