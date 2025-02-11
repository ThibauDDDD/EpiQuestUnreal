#include "MapMarker2d.h"
#include "PaperSpriteComponent.h"
//#include "PaperSprite.h"
#include "UObject/ConstructorHelpers.h"

// Constructor
AMapMarker2d::AMapMarker2d()
{
    // Définit le tick par défaut
    PrimaryActorTick.bCanEverTick = true;

    // Création du PaperSpriteComponent et ajout à l'Actor
    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
    SpriteComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Canal personnalisé
    SpriteComponent->SetRenderCustomDepth(true); // Active le Custom Depth
    SpriteComponent->SetVisibility(true);
    RootComponent = SpriteComponent; // Définit le SpriteComponent comme root du actor

    // Si un sprite est défini via Blueprint, nous l'affectons à notre SpriteComponent
    /*if (Sprite)
    {
        SpriteComponent->SetSprite(Sprite);
    }*/
}

// Fonction appelée au début
void AMapMarker2d::BeginPlay()
{
    Super::BeginPlay();

    // Vérifie à nouveau si un sprite est défini en Blueprint
    /*if (Sprite && !SpriteComponent->GetSprite())
    {
        SpriteComponent->SetSprite(Sprite);
    }*/
}

// Fonction appelée à chaque frame
void AMapMarker2d::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
