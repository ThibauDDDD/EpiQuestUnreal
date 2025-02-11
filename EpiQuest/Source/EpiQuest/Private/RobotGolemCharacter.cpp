#include "RobotGolemCharacter.h"

ARobotGolemCharacter::ARobotGolemCharacter()
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

    PrimaryActorTick.bCanEverTick = true;
    // Charger et assigner le Skeletal Mesh pour le buste
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/Assets/Undercity/UnderCity/Demo/StarterContent/Particles/P_Smoke.P_Smoke"));
    if (ParticleAsset.Succeeded())
    {
        ParticleSystemComponent->SetTemplate(ParticleAsset.Object);
    }

    IsBrocken = true;

}

// Called when the game starts or when spawned
void ARobotGolemCharacter::BeginPlay()
{
	Super::BeginPlay();
    FTimerHandle TimerHandle;

    //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ARobot::CreateAndShowWidget, 10.0f, false);
    if (IsBrocken) {
        SetMeshVisibility(RobotMeshSpinner, false);
        SetMeshVisibility(RobotMeshWheel, false);
    }
}

// Called every frame
void ARobotGolemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARobotGolemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARobotGolemCharacter::SetMeshVisibility(USkeletalMeshComponent* MeshRobot, bool bVisible)
{
    if (MeshRobot)
    {
        ParticleSystemComponent->SetVisibility(bVisible);
        MeshRobot->SetVisibility(bVisible);
        MeshRobot->SetHiddenInGame(!bVisible);
        bVisible ? MeshRobot->SetCollisionEnabled(ECollisionEnabled::NoCollision) :
            MeshRobot->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    }
}


void ARobotGolemCharacter::CreateAndShowWidget()
{
    if (!WidgetClass) // Vérifie si la classe de widget est définie
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("sdcsvsdv réussie !"));
        return;
    }
    if (!IsBrocken) {
        return;
    }
    // Vérifie si le widget n'existe pas déjà

    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" existe!"));

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    // Crée une instance du widget
    WidgetInstance = CreateWidget<UIDESystem>(PlayerController, WidgetClass);

    if (WidgetInstance)
    {
        // Affiche le widget sur l'écran
        WidgetInstance->AddToViewport();
        WidgetInstance->FileName = PythonFileName;
        WidgetInstance->RobotGolemCharacter = this;
        WidgetInstance->CopyFilesToSavedFolder();
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, "Widget créé " + WidgetInstance->FileName);
        PlayerController->SetPause(true);
        PlayerController->SetShowMouseCursor(true);
    }
}