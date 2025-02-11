// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "BetterMultiLineEditableTextBox.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/PlatformProcess.h"
#include "Misc/OutputDeviceNull.h"
#include "Misc/OutputDeviceFile.h"
#include "Misc/DateTime.h"
#include "Sound/SoundWave.h"

#include "IDESystem.generated.h"

class ARobotGolemCharacter;
class AEpiQuestCharacter;

/**
 * 
 */
UCLASS()
class EPIQUEST_API UIDESystem : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:


	UPROPERTY(EditAnywhere, Category = "Robot")
	ARobotGolemCharacter* RobotGolemCharacter;


	UFUNCTION()
	void CopyFilesToSavedFolder();


	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundWave* MySoundWave;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Play;
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_CloseTerminal;
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_CloseVSCode;
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_ReloadVSCode;
	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Correct;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UBetterMultiLineEditableTextBox* BetterMultiLineEditableTextBox;

	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	class UImage* Image_TerminalVSCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock *TextBlock_Terminal;

	FString SourcePath;
	FString ContentOrigin;
	FString DestinationPath;
	FString DestinationPathSolution;
	FString DestinationFolder;
	IPlatformFile *PlatformFile;
private:
	UFUNCTION()
	void CopyFileToSavedFolder(bool Solution);
	UFUNCTION()
	void OnPlayClicked();
	UFUNCTION()
	void GoToTerminal();
	UFUNCTION()
	void GoToVSCode();
	UFUNCTION()
	bool CheckSolutions();
	UFUNCTION()
	FString ExecutePythonScript(bool Solution);
	UFUNCTION()
	void PrintOutputToConsole(FString Output);
	UFUNCTION()
	void CorrectAnswer();
	UFUNCTION()
	void QuitVSCode();


};
