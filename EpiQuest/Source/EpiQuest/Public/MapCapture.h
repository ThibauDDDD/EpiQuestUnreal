#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapCapture.generated.h"

// Forward declarations
class USceneCaptureComponent2D;
class UTextureRenderTarget2D;

UCLASS()
class EPIQUEST_API AMapCapture : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values
    AMapCapture();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Scene Capture Component to capture the mini-map view
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
    USceneCaptureComponent2D* SceneCaptureComponent;

    // Texture where the mini-map view will be rendered
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
    UTextureRenderTarget2D* RenderTarget;

    // Function to manually update the capture
    UFUNCTION(BlueprintCallable, Category = "Map")
    void UpdateCapture();
};
