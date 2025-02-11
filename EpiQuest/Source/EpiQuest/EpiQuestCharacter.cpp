// Copyright Epic Games, Inc. All Rights Reserved.

#include "EpiQuestCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "Engine/World.h"   // Pour GetWorld()
#include "GameFramework/Actor.h"  // Pour AActor et TActorIterator
#include "Camera/PlayerCameraManager.h"  // Pour obtenir la caméra principale

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AEpiQuestCharacter

AEpiQuestCharacter::AEpiQuestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.20f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm



	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AEpiQuestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	//{
	//	AActor* Actor = *ActorItr;
	//	if (Actor && Actor->IsValidLowLevel() && Actor->Tags.Contains(FName("MapOnly3")))
	//	{
	//		// S'assurer que l'acteur est valide avant de le manipuler
	//		Actor->SetActorHiddenInGame(true); // Masque l'acteur dans la vue principale
	//	}
	//}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEpiQuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Associer la touche E à la fonction InteractWithRobot
	PlayerInputComponent->BindAction("Interract", IE_Pressed, this, &AEpiQuestCharacter::InteractWithRobot);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEpiQuestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEpiQuestCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AEpiQuestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEpiQuestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AEpiQuestCharacter::InteractWithRobot()
{

	float NearestDistance = 650.0f; // Rayon de détection
	RobotGolemCharacter = nullptr;

	for (TActorIterator<ARobotGolemCharacter> It(GetWorld()); It; ++It)
	{
		ARobotGolemCharacter* NearestRobot = *It;
		FString RobotName = NearestRobot->GetName(); // Obtenir le nom du robot

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, NearestRobot->GetActorLocation().ToString());

		float Distance = FVector::Dist(this->GetActorLocation(), NearestRobot->GetActorLocation());
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::SanitizeFloat(Distance));

		if (Distance < NearestDistance)
		{
			NearestRobot->CreateAndShowWidget(); // Appeler la fonction d'interaction du robot
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Interaction réussie !"));
		}
	}

}


void AEpiQuestCharacter::Win()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" VICTOIRE"));

}


// Fonction pour masquer les acteurs dans la caméra principale uniquement
void AEpiQuestCharacter::HideActorsForMainCamera()
{
	// Vérifie la caméra principale
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	if (CameraManager)
	{
		FVector CameraLocation = CameraManager->GetCameraLocation();
		FRotator CameraRotation = CameraManager->GetCameraRotation();

		// Boucle sur les acteurs
		for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			AActor* Actor = *ActorItr;

			if (Actor && Actor->Tags.Contains(FName("MapOnly3")))
			{
				// Vérifier si l'acteur est dans la vue de la caméra
				if (IsActorVisibleFromCamera(CameraLocation, CameraRotation, Actor))
				{
					Actor->SetActorHiddenInGame(true); // Masquer dans la vue principale
				}
				else
				{
					Actor->SetActorHiddenInGame(false); // Ne pas masquer dans la minimap
				}
			}
		}
	}
}

// Fonction pour vérifier si l'acteur est visible depuis la caméra
bool AEpiQuestCharacter::IsActorVisibleFromCamera(const FVector& CameraLocation, const FRotator& CameraRotation, AActor* Actor)
{
	FVector ActorLocation = Actor->GetActorLocation();

	// Calculer si l'acteur est dans le champ de vision de la caméra (plus logique à personnaliser selon ton jeu)
	FVector DirectionToActor = ActorLocation - CameraLocation;
	float DotProduct = FVector::DotProduct(CameraRotation.Vector(), DirectionToActor.GetSafeNormal());

	// Si l'acteur est suffisamment dans le champ de vision de la caméra
	return DotProduct > 0.5f;  // Ajuste ce seuil pour mieux adapter au jeu
}

void AEpiQuestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HideActorsForMainCamera();
}