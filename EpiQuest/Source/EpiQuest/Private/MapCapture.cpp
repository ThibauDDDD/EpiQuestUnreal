#include "MapCapture.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/World.h"

// Sets default values
AMapCapture::AMapCapture()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create and attach the Scene Capture Component 2D
    SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCaptureComponent"));
    RootComponent = SceneCaptureComponent;

    // Set default properties
    SceneCaptureComponent->bCaptureEveryFrame = true;
    SceneCaptureComponent->bCaptureOnMovement = false;

    // Create a default render target
    RenderTarget = NewObject<UTextureRenderTarget2D>();
    if (RenderTarget)
    {
        RenderTarget->InitAutoFormat(1024, 1024);
        SceneCaptureComponent->TextureTarget = RenderTarget;
    }
}

// Called when the game starts
void AMapCapture::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AMapCapture::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Manually update the scene capture
void AMapCapture::UpdateCapture()
{
    if (SceneCaptureComponent)
    {
        SceneCaptureComponent->CaptureScene();
    }
}
