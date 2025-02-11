#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h" 
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "IDESystem.h"
#include "Particles/ParticleSystemComponent.h"


class UIDESystem;

#include "Robot.generated.h"

UCLASS()
class EPIQUEST_API ARobot : public AActor
{
    GENERATED_BODY()

public:
    ARobot();
    UIDESystem* IDESystem;

protected:
    virtual void BeginPlay() override;

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
    UParticleSystemComponent* ParticleSystemComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    USkeletalMeshComponent* RobotMeshBody;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    USkeletalMeshComponent* RobotMeshWheel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meshes")
    USkeletalMeshComponent* RobotMeshSpinner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Robot")
    FString PythonFileName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Robot")
    bool IsBrocken;

    UFUNCTION()
    void SetMeshVisibility(USkeletalMeshComponent* Mesh, bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void CreateAndShowWidget();

    UPROPERTY(EditAnywhere, Category = "Robot")
    TSubclassOf<UIDESystem> WidgetClass;

    UPROPERTY()
    UIDESystem* WidgetInstance;

};
