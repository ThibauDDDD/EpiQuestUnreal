#include "EpiQuestGameMode.h"
#include "EpiQuestCharacter.h"
#include "EpiQuestPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AEpiQuestGameMode::AEpiQuestGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/Engine.Blueprint'/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter.BP_ThirdPersonCharacter'"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = AEpiQuestPlayerController::StaticClass();
}