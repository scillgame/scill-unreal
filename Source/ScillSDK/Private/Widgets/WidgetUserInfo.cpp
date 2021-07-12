// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetUserInfo.h"

UWidgetUserInfo::UWidgetUserInfo(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UWidgetUserInfo::NativeConstruct()
{
    Super::NativeConstruct();

    auto Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (Controller)
    {
        ScillClient = Controller->FindComponentByClass<UScillClient>();
    }

    FScriptDelegate buttonClickedDelegate;
    buttonClickedDelegate.BindUFunction(this, "SetUserDataClicked");
    SetUserData->OnReleased.Add(buttonClickedDelegate);

    QueryUserInfo();
}

void UWidgetUserInfo::SetUserDataClicked()
{
    FUserInfoReceived Delegate;
    FUserInfo ui;
    ui.Username = UserName->GetText().ToString();
    ui.AvatarImage = AvatarImage;
    ScillClient->SetUserData(ui, Delegate);
}

void UWidgetUserInfo::QueryUserInfo()
{
    if (ScillClient)
    {
        FUserInfoReceived Delegate;
        Delegate.BindDynamic(this, &UWidgetUserInfo::ReceiveUserInfo);

        ScillClient->GetUserData(Delegate);
    }
}

void UWidgetUserInfo::ReceiveUserInfo(const FUserInfo& UserInfo, bool Success)
{
    if (Success)
    {
        this->UserName->SetText(FText::FromString(UserInfo.Username));
        this->AvatarImage = UserInfo.AvatarImage;
    }
}