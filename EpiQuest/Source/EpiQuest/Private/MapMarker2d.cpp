#include "MapMarker2d.h"
#include "PaperSpriteComponent.h"
//#include "PaperSprite.h"
#include "UObject/ConstructorHelpers.h"

// Constructor
AMapMarker2d::AMapMarker2d()
{
    // D�finit le tick par d�faut
    PrimaryActorTick.bCanEverTick = true;

    // Cr�ation du PaperSpriteComponent et ajout � l'Actor
    SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
    SpriteComponent->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Canal personnalis�
    SpriteComponent->SetRenderCustomDepth(true); // Active le Custom Depth
    SpriteComponent->SetVisibility(true);
    RootComponent = SpriteComponent; // D�finit le SpriteComponent comme root du actor

    // Si un sprite est d�fini via Blueprint, nous l'affectons � notre SpriteComponent
    /*if (Sprite)
    {
        SpriteComponent->SetSprite(Sprite);
    }*/
}

// Fonction appel�e au d�but
void AMapMarker2d::BeginPlay()
{
    Super::BeginPlay();

    // V�rifie � nouveau si un sprite est d�fini en Blueprint
    /*if (Sprite && !SpriteComponent->GetSprite())
    {
        SpriteComponent->SetSprite(Sprite);
    }*/
}

// Fonction appel�e � chaque frame
void AMapMarker2d::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
