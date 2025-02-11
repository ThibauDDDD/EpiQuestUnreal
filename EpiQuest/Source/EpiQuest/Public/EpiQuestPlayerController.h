#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EpiQuestPlayerController.generated.h"

/**
 * PlayerController personnalisé pour gérer les déplacements et les interactions du joueur.
 */
UCLASS()
class EPIQUEST_API AEpiQuestPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	
	void MoveRight(float Value);

	
	void MoveForward(float Value);

	
	void StartJump();
	void StopJump();
};