#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"

/**
 * Widget du menu principal.
 */

UCLASS()
class EPIQUEST_API UPauseMenu : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    UPROPERTY(meta = (BindWidget))
    class UButton* ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UButton* MenuButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_Title;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_ResumeButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_OptionsButton;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Txt_MenuButton;

    // Classe du widget d'options
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TSubclassOf<UUserWidget> OptionsWidgetClass;

private:
    UFUNCTION()
    void OnResumeClicked();

    UFUNCTION()
    void OnOptionsClicked();

    UFUNCTION()
    void OnMenuClicked();
};