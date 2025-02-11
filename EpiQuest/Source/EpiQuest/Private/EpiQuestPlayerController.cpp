#include "EpiQuestPlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Robot.h"

void AEpiQuestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &AEpiQuestPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AEpiQuestPlayerController::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AEpiQuestPlayerController::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AEpiQuestPlayerController::StopJump);
}

void AEpiQuestPlayerController::MoveForward(float Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(FVector::ForwardVector, Value);
	}
}

void AEpiQuestPlayerController::MoveRight(float Value)
{
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(FVector::RightVector, Value);
	}
}

void AEpiQuestPlayerController::StartJump()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
	{
		ControlledCharacter->Jump();
	}
}

void AEpiQuestPlayerController::StopJump()
{
	if (ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn()))
	{
		ControlledCharacter->StopJumping();
	}
}



