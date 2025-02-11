#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "PaperSpriteComponent.h"  // Inclure le header nécessaire pour PaperSpriteComponent
//#include "PaperSprite.h"  // Assurez-vous d'inclure ce header pour travailler avec des sprites
#include "MapMarker2d.generated.h"

class UPaperSprite;
class UPaperSpriteComponent;

UCLASS()
class EPIQUEST_API AMapMarker2d : public AActor
{
    GENERATED_BODY()

public:
    // Déclaration du composant PaperSprite
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Sprite")
    UPaperSpriteComponent* SpriteComponent;

    // Déclaration de la propriété exposée pour le sprite (permet de définir un sprite via Blueprint)
    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sprite")
    UPaperSprite* Sprite;*/

    // Constructeur
    AMapMarker2d();

protected:
    // Fonction appelée au début
    virtual void BeginPlay() override;

public:
    // Fonction appelée à chaque frame
    virtual void Tick(float DeltaTime) override;
};
