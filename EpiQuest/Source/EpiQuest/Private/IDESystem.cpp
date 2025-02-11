// Fill out your copyright notice in the Description page of Project Settings.


#include "IDESystem.h"
#include "RobotGolemCharacter.h"
#include "../EpiQuestCharacter.h"



FReply UIDESystem::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
    if (InKeyEvent.GetKey() == EKeys::Tab)
    {
        // Empêche la touche Tab d'effectuer son action par défaut
        auto SW = StaticCastSharedRef<SMultiLineEditableTextBox>(BetterMultiLineEditableTextBox->TakeWidget());

        SW->InsertTextAtCursor("    ");
        return FReply::Handled();
    }

    // Appelle le comportement par défaut pour les autres touches
    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}


void UIDESystem::NativeConstruct()
{
	Super::NativeConstruct();

	if (Btn_Play) {
		Btn_Play->OnClicked.AddDynamic(this, &UIDESystem::OnPlayClicked);	
	}
    if (Btn_ReloadVSCode) {
        Btn_ReloadVSCode->OnClicked.AddDynamic(this, &UIDESystem::CopyFilesToSavedFolder);
    }
    if (Btn_CloseTerminal) {
        Btn_CloseTerminal->OnClicked.AddDynamic(this, &UIDESystem::GoToVSCode);
    }
    if (Btn_CloseVSCode) {
        Btn_CloseVSCode->OnClicked.AddDynamic(this, &UIDESystem::QuitVSCode);
    }
    if (Btn_Correct) {
        Btn_Correct->OnClicked.AddDynamic(this, &UIDESystem::CorrectAnswer);
    }
    UIDESystem::GoToVSCode();

}

void UIDESystem::QuitVSCode()
{

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->SetPause(false);
    PlayerController->SetShowMouseCursor(false);
    RemoveFromParent();
}

void UIDESystem::CorrectAnswer()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    AEpiQuestCharacter* Ruby = Cast<AEpiQuestCharacter>(PlayerController->GetPawn());
    PlayerController->SetPause(false);
    PlayerController->SetShowMouseCursor(false);
    UGameplayStatics::PlaySound2D(GetWorld(), MySoundWave);
    GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, RobotGolemCharacter->PythonFileName);
    RobotGolemCharacter->SetMeshVisibility(RobotGolemCharacter->RobotMeshSpinner, true);
    RobotGolemCharacter->SetMeshVisibility(RobotGolemCharacter->RobotMeshWheel, true);
    RobotGolemCharacter->IsBrocken = false;
    RobotGolemCharacter->ParticleSystemComponent->SetVisibility(false);
    Ruby->RepairedRobotNbr += 1;
    Ruby->Hud->TextRepearedRobot->SetText(FText::FromString(FString::FromInt(Ruby->RepairedRobotNbr) + TEXT(" / 10")));
    RemoveFromParent();
}

void UIDESystem::OnPlayClicked()
{
	if (BetterMultiLineEditableTextBox) {
		auto TextString = BetterMultiLineEditableTextBox->GetText().ToString();
		FFileHelper::SaveStringToFile(TextString, *DestinationPath);
        bool Correct = CheckSolutions();
        UIDESystem::GoToTerminal();
    }
}

void UIDESystem::GoToVSCode()
{
    BetterMultiLineEditableTextBox->SetVisibility(ESlateVisibility::Visible);
    Btn_Play->SetVisibility(ESlateVisibility::Visible);
    Btn_CloseVSCode->SetVisibility(ESlateVisibility::Visible);
    Btn_ReloadVSCode->SetVisibility(ESlateVisibility::Visible);
    Image_TerminalVSCode->SetVisibility(ESlateVisibility::Collapsed);
    TextBlock_Terminal->SetVisibility(ESlateVisibility::Collapsed);
    Btn_CloseTerminal->SetVisibility(ESlateVisibility::Collapsed);
    Btn_Correct->SetVisibility(ESlateVisibility::Collapsed);
    PrintOutputToConsole("");
}

void UIDESystem::GoToTerminal()
{
    BetterMultiLineEditableTextBox->SetVisibility(ESlateVisibility::Collapsed);
    Btn_Play->SetVisibility(ESlateVisibility::Collapsed);
    Btn_CloseVSCode->SetVisibility(ESlateVisibility::Collapsed);
    Btn_ReloadVSCode->SetVisibility(ESlateVisibility::Collapsed);
    Image_TerminalVSCode->SetVisibility(ESlateVisibility::Visible);
    TextBlock_Terminal->SetVisibility(ESlateVisibility::Visible);
    Btn_CloseTerminal->SetVisibility(ESlateVisibility::Visible);
}

void UIDESystem::CopyFilesToSavedFolder()
{
    CopyFileToSavedFolder(false);
    BetterMultiLineEditableTextBox->SetText(FText::FromString(ContentOrigin));
    CopyFileToSavedFolder(true);
}


void UIDESystem::CopyFileToSavedFolder(bool solution)
{

    DestinationFolder = FPaths::ProjectSavedDir() + TEXT("Scripts_Python/");
    SourcePath = FPaths::ProjectContentDir() + TEXT("Scripts_Python/" + FileName);
    DestinationPath = FPaths::ProjectSavedDir() + TEXT("Scripts_Python/" + FileName);
    if (solution) 
    {
        SourcePath.RemoveFromEnd(".py");
        SourcePath += "_solution.py";
        DestinationPath.RemoveFromEnd(".py");
        DestinationPath += "_solution.py";
    }

    PlatformFile = &FPlatformFileManager::Get().GetPlatformFile();

	// create the directory in saved follder if it doesn't exist
	if (!PlatformFile->DirectoryExists(*DestinationFolder))
	{
		PlatformFile->CreateDirectory(*DestinationFolder);
	}

	// delete the file in saved Scipts_Python folder if it exist
	if (PlatformFile->FileExists(*DestinationPath))
	{
		PlatformFile->DeleteFile(*DestinationPath);
	}

	// copy the file in saved Script_python folder
	if (FPaths::FileExists(SourcePath) && !FPaths::FileExists(DestinationPath))
	{
		FPlatformFileManager::Get().GetPlatformFile().CopyFile(*DestinationPath, *SourcePath);
	}
    if (solution)
    {
        SourcePath.RemoveFromEnd("_solution.py");
        SourcePath += ".py";
        DestinationPath.RemoveFromEnd("_solution.py");
        DestinationPath += ".py";
    }
	FFileHelper::LoadFileToString(ContentOrigin, *SourcePath);
}

void UIDESystem::PrintOutputToConsole(FString Output)
{
    TextBlock_Terminal->SetText(FText::FromString(Output));
}


bool UIDESystem::CheckSolutions()
{
    FString ExerciceOutput = ExecutePythonScript(false);
    FString SolutionOutput = ExecutePythonScript(true);
    PrintOutputToConsole(ExerciceOutput);
    if (ExerciceOutput != SolutionOutput) {
        return (false);
    }
    Btn_Correct->SetVisibility(ESlateVisibility::Visible);
    return (true);
}


FString UIDESystem::ExecutePythonScript(bool solution)
{
    // Définir les chemins de l'exécutable Python et du script
    FString PythonExecutable = FPaths::Combine(FPaths::ProjectDir(), TEXT("ThirdParty/Python/python.exe"));
    if (solution) {
        DestinationPath.RemoveFromEnd(".py");
        DestinationPath += "_solution.py";
    }

    // Commande pour exécuter le script
    FString Command = FString::Printf(TEXT("\"%s\" \"%s\""), *PythonExecutable, *DestinationPath);

    // Créer les pipes pour rediriger les sorties
    void* ReadPipe = nullptr;
    void* WritePipe = nullptr;
    FPlatformProcess::CreatePipe(ReadPipe, WritePipe);

    // Lancer le processus
    FProcHandle ProcessHandle = FPlatformProcess::CreateProc(
        *PythonExecutable,                   // Chemin de l'exécutable
        *FString::Printf(TEXT("\"%s\""), *DestinationPath), // Arguments
        true,                                // Mode sans interface utilisateur
        true,                                // Bloquer l'interface utilisateur
        true,                                // Rediriger les sorties
        nullptr,                             // Identifiant utilisateur (NULL)
        0,                                   // Priorité
        nullptr,                             // Environnement (NULL)
        WritePipe                            // Redirection de la sortie
    );

    // Lire les sorties
    FString Output;
    FString Error;
    while (FPlatformProcess::IsProcRunning(ProcessHandle))
    {
        FString NewOutput = FPlatformProcess::ReadPipe(ReadPipe);
        if (!NewOutput.IsEmpty())
        {
            Output += NewOutput;
        }
        FPlatformProcess::Sleep(0.1f);
    }

    // Assurez-vous de récupérer les derniers messages après la fin
    FString FinalOutput = FPlatformProcess::ReadPipe(ReadPipe);
    if (!FinalOutput.IsEmpty())
    {
        Output += FinalOutput;
    }

    // Fermer les pipes et libérer les ressources
    FPlatformProcess::ClosePipe(ReadPipe, WritePipe);
    FPlatformProcess::WaitForProc(ProcessHandle);
    FPlatformProcess::TerminateProc(ProcessHandle);

    if (solution) {
        DestinationPath.RemoveFromEnd("_solution.py");
        DestinationPath += ".py";
    }
    return (Output);
}

