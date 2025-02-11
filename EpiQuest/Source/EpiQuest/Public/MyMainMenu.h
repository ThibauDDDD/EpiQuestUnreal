#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Misc/Paths.h"
#include "Engine/Engine.h"

#include "MyMainMenu.generated.h"

/**
 * Widget du menu principal.
 */

UCLASS()
class EPIQUEST_API UMyMainMenu : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    
    UPROPERTY(meta = (BindWidget))
    class UButton* PlayButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* QuitButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_Title;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_PlayButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_QuitButton;

    // Classe du widget d'options
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TSubclassOf<UUserWidget> OptionsWidgetClass;

private:
    UFUNCTION()
    void OnPlayClicked();

    UFUNCTION()
    void OnOptionsClicked();

    UFUNCTION()
    void OnQuitClicked();
};
