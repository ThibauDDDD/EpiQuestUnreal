#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PaperSpriteComponent.h"  // Inclure le header n�cessaire pour PaperSpriteComponent
//#include "PaperSprite.h"  // Assurez-vous d'inclure ce header pour travailler avec des sprites
#include "MapMarker2d.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;

UCLASS()
class EPIQUEST_API AMapMarker2d : public AActor
{
    GENERATED_BODY()

public:
    // D�claration du composant PaperSprite
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprite")
    UPaperSpriteComponent* SpriteComponent;

    // D�claration de la propri�t� expos�e pour le sprite (permet de d�finir un sprite via Blueprint)
    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
    UPaperSprite* Sprite;*/

    // Constructeur
    AMapMarker2d();

protected:
    // Fonction appel�e au d�but
    virtual void BeginPlay() override;

public:
    // Fonction appel�e � chaque frame
    virtual void Tick(float DeltaTime) override;
};
