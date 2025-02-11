#include "Robot.h"

ARobot::ARobot()
{

    RobotMeshBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Golem"));
    RobotMeshWheel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Wheel"));
    RobotMeshSpinner = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spinner"));
    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

    RootComponent = RobotMeshBody;

    RobotMeshWheel->SetupAttachment(RobotMeshBody, "headSocket");
    RobotMeshSpinner->SetupAttachment(RobotMeshBody, "Spine_03");
    ParticleSystemComponent->SetupAttachment(RootComponent, "HeadSosket");
    ParticleSystemComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));
    ParticleSystemComponent->SetRelativeRotation(FRotator(50.f, 0.f, 0.f));
    RobotMeshWheel->SetRelativeLocation(FVector(6.f, 0.f, -34.f));
    RobotMeshSpinner->SetRelativeLocation(FVector(-6.f, -3.f, 0.f));
    RobotMeshSpinner->SetRelativeRotation(FRotator(-90.f, 0.f, 10.f));
    SetMeshVisibility(RobotMeshWheel, true);
    SetMeshVisibility(RobotMeshSpinner, true);

    PrimaryActorTick.bCanEverTick = true;
    // Charger et assigner le Skeletal Mesh pour le buste
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Assets/Undercity/UnderCity/Demo/StarterContent/Particles/P_Smoke.P_Smoke"));
    if (ParticleAsset.Succeeded())
    {
        ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
    }

    IsBrocken = true;
}

void ARobot::BeginPlay()
{
    Super::BeginPlay();
    FTimerHandle TimerHandle;
    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARobot::CreateAndShowWidget, 10.0f, false);
    if (IsBrocken) {
        SetMeshVisibility(RobotMeshSpinner, false);
        SetMeshVisibility(RobotMeshWheel, false);
    }
    
}

void ARobot::SetMeshVisibility(USkeletalMeshComponent* Mesh, bool bVisible)
{
    if (Mesh)
    {
        Mesh->SetVisibility(bVisible);
        Mesh->SetHiddenInGame(!bVisible);
    }
}

void ARobot::CreateAndShowWidget()
{
    if (!WidgetClass) // V�rifie si la classe de widget est d�finie
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("sdcsvsdv r�ussie !"));
        return;
    }
    if (!IsBrocken) {
        return;
    }
    // V�rifie si le widget n'existe pas d�j�
    
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" existe!"));

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    // Cr�e une instance du widget
    WidgetInstance = CreateWidget<UIDESystem>(PlayerController, WidgetClass);

    if (WidgetInstance)
    {
        // Affiche le widget sur l'�cran
        WidgetInstance->AddToViewport();
        WidgetInstance->FileName = PythonFileName;
        //WidgetInstance->Robot = this;
        WidgetInstance->CopyFilesToSavedFolder();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Widget cr�� " + WidgetInstance->FileName);
        PlayerController->SetPause(true);
        PlayerController->SetShowMouseCursor(true);
    }
}