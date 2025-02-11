// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/WidgetBlueprintLibrary.h" 
#include "Misc/Paths.h"
#include "Kismet/GameplayStatics.h"
#include "IDESystem.h"
#include "Particles/ParticleSystemComponent.h"


class UIDESystem;

#include "RobotGolemCharacter.generated.h"

UCLASS()
class EPIQUEST_API ARobotGolemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobotGolemCharacter();
	UIDESystem* IDESystem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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
    void SetMeshVisibility(USkeletalMeshComponent* MeshRobot, bool bVisible);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void CreateAndShowWidget();

    UPROPERTY(EditAnywhere, Category = "Robot")
    TSubclassOf<UIDESystem> WidgetClass;

    UPROPERTY()
    UIDESystem* WidgetInstance;
};
