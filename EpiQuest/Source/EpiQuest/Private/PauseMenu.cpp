// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void UPauseMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (ResumeButton)
    {
        ResumeButton->OnClicked.AddDynamic(this, &UPauseMenu::OnResumeClicked);
    }

    if (OptionsButton)
    {
        OptionsButton->OnClicked.AddDynamic(this, &UPauseMenu::OnOptionsClicked);
    }

    if (MenuButton)
    {
        MenuButton->OnClicked.AddDynamic(this, &UPauseMenu::OnMenuClicked);
    }

    if (Txt_Title)
    {
        Txt_Title->SetText(FText::FromString("PAUSE"));
    }

    if (Txt_ResumeButton)
    {
        Txt_ResumeButton->SetText(FText::FromString("Resume"));
    }

    if (Txt_OptionsButton)
    {
        Txt_OptionsButton->SetText(FText::FromString("Option"));
    }

    if (Txt_MenuButton)
    {
        Txt_MenuButton->SetText(FText::FromString("Menu"));
    }

}

void UPauseMenu::OnResumeClicked()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    PlayerController->SetPause(false);
    PlayerController->SetShowMouseCursor(false);
    RemoveFromParent();
}

void UPauseMenu::OnOptionsClicked()
{
    if (OptionsWidgetClass)
    {

        UUserWidget* OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);
        if (OptionsWidget)
        {
            OptionsWidget->AddToViewport();
            //RemoveFromParent();
        }
    }

}

void UPauseMenu::OnMenuClicked()
{
    RemoveFromParent();
    UGameplayStatics::OpenLevel(this, FName("mainMenu"));
}

