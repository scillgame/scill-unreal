// Copyright Epic Games, Inc. All Rights Reserved.


#include "Widgets/WidgetChallenge.h"
#include "Blueprint/WidgetTree.h"
#include "Components/PanelWidget.h"

UWidgetChallenge::UWidgetChallenge(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    
}

void UWidgetChallenge::NativeConstruct()
{
    Super::NativeConstruct();

    UPanelWidget* RootWidget = Cast<UPanelWidget>(GetRootWidget());

    if (!TestButton)
    {
        TestButton = WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(), TEXT("MyButton"));

        RootWidget->AddChild(TestButton);
    }
}
