#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Components/Widget.h"
#include "RobotGolemCharacter.h"
#include "EngineUtils.h"
#include "HudPlayer.h"


#include "EpiQuestCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AEpiQuestCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)//, BlueprintReadWrite, Category = "Robot")
	USkeletalMeshComponent* PlayerMesh;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AEpiQuestCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	ARobotGolemCharacter* RobotGolemCharacter;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UHudPlayer* Hud;
	UFUNCTION(BlueprintCallable, Category = "Robot")
	void InteractWithRobot();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Win")
	int32 RepairedRobotNbr;

	UFUNCTION(BlueprintCallable, Category = "Win")
	void Win();

	UFUNCTION()
	void HideActorsForMainCamera();
	UFUNCTION()
	bool IsActorVisibleFromCamera(const FVector& CameraLocation, const FRotator& CameraRotation, AActor* Actor);

	virtual void Tick(float DeltaTime) override;

};

