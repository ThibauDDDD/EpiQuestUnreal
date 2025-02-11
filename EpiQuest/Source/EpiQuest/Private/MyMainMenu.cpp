#include "MyMainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


void UMyMainMenu::NativeConstruct()
{
    Super::NativeConstruct();

    if (PlayButton)
    {
        PlayButton->OnClicked.AddDynamic(this, &UMyMainMenu::OnPlayClicked);
    }

    if (OptionsButton)
    {
        OptionsButton->OnClicked.AddDynamic(this, &UMyMainMenu::OnOptionsClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMyMainMenu::OnQuitClicked);
    }

    if (Txt_Title)
    {
        Txt_Title->SetText(FText::FromString("EPIQUEST"));
    }

    if (Txt_PlayButton)
    {
        Txt_PlayButton->SetText(FText::FromString("Play"));
    }

    if (Txt_OptionsButton)
    {
        Txt_OptionsButton->SetText(FText::FromString("Option"));
    }

    if (Txt_QuitButton)
    {
        Txt_QuitButton->SetText(FText::FromString("Quit"));
    }

}

void UMyMainMenu::OnPlayClicked()
{
    UGameplayStatics::OpenLevel(this, FName("Level2"));
}

void UMyMainMenu::OnOptionsClicked()
{
    if (OptionsWidgetClass)
    {
        
        UUserWidget* OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), OptionsWidgetClass);
        if (OptionsWidget)
        {
            OptionsWidget->AddToViewport();
            RemoveFromParent(); 
        }
    }

}

void UMyMainMenu::OnQuitClicked()
{

    UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}