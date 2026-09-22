#include "Misc/AutomationTest.h"
#include "System/Battle/StatComponents/AttributeComponent.h"
#include "TestDummy/AttributeComponentTestListener.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(AttributeComponentTest, "P3R_Clone.P3R_Clone.Private.Test.AttributeComponentTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool AttributeComponentTest::RunTest(const FString& Parameters)
{
         // =========================================================
    // Setup
    // =========================================================

    UAttributeComponent* AttributeComponent =
        NewObject<UAttributeComponent>();

    TestNotNull(
        TEXT("AttributeComponent should be created"),
        AttributeComponent
    );

    if (!AttributeComponent)
    {
        return false;
    }

    UAttributeComponentTestListener* Listener =
        NewObject<UAttributeComponentTestListener>();

    TestNotNull(
        TEXT("Test listener should be created"),
        Listener
    );

    if (!Listener)
    {
        return false;
    }


    const FDelegateHandle HPHandle =
        AttributeComponent->AddStatListener(
            EP3R_StatType::HP,
            Listener,
            &UAttributeComponentTestListener::OnHPChanged
        );

    const FDelegateHandle MaxHPHandle =
        AttributeComponent->AddStatListener(
            EP3R_StatType::MaxHP,
            Listener,
            &UAttributeComponentTestListener::OnMaxHPChanged
        );

    const FDelegateHandle SPHandle =
        AttributeComponent->AddStatListener(
            EP3R_StatType::SP,
            Listener,
            &UAttributeComponentTestListener::OnSPChanged
        );

    const FDelegateHandle MaxSPHandle =
        AttributeComponent->AddStatListener(
            EP3R_StatType::MaxSP,
            Listener,
            &UAttributeComponentTestListener::OnMaxSPChanged
        );


    // =========================================================
    // 1. Initial Value
    // =========================================================

    TestEqual(
        TEXT("Initial HP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        0.f
    );

    TestEqual(
        TEXT("Initial HP Current"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        0.f
    );

    TestEqual(
        TEXT("Initial MaxHP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::MaxHP),
        0.f
    );

    TestEqual(
        TEXT("Initial MaxHP Current"),
        AttributeComponent->GetStat(EP3R_StatType::MaxHP),
        0.f
    );

    TestEqual(
        TEXT("Initial SP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::SP),
        0.f
    );

    TestEqual(
        TEXT("Initial SP Current"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        0.f
    );

    TestEqual(
        TEXT("Initial MaxSP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::MaxSP),
        0.f
    );

    TestEqual(
        TEXT("Initial MaxSP Current"),
        AttributeComponent->GetStat(EP3R_StatType::MaxSP),
        0.f
    );


    // =========================================================
    // 2. Set / Getter
    // =========================================================

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxHP,
        100.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        80.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxSP,
        50.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::SP,
        30.f
    );

    TestEqual(
        TEXT("MaxHP"),
        AttributeComponent->GetStat(EP3R_StatType::MaxHP),
        100.f
    );

    TestEqual(
        TEXT("HP"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        80.f
    );

    TestEqual(
        TEXT("MaxSP"),
        AttributeComponent->GetStat(EP3R_StatType::MaxSP),
        50.f
    );

    TestEqual(
        TEXT("SP"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        30.f
    );

    TestEqual(
        TEXT("HP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        80.f
    );

    TestEqual(
        TEXT("MaxHP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::MaxHP),
        100.f
    );

    TestEqual(
        TEXT("SP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::SP),
        30.f
    );

    TestEqual(
        TEXT("MaxSP Base"),
        AttributeComponent->GetStatBase(EP3R_StatType::MaxSP),
        50.f
    );


    // =========================================================
    // 3. Increase
    // =========================================================

    Listener->ClearEvents();

    AttributeComponent->IncreaseStatBase(
        EP3R_StatType::HP,
        10.f
    );

    TestEqual(
        TEXT("HP Increase"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        90.f
    );

    TestEqual(
        TEXT("HP Base After Increase"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        90.f
    );

    AttributeComponent->IncreaseStatBase(
        EP3R_StatType::SP,
        10.f
    );

    TestEqual(
        TEXT("SP Increase"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        40.f
    );


    // =========================================================
    // 4. Decrease
    // =========================================================

    AttributeComponent->DecreaseStatBase(
        EP3R_StatType::HP,
        20.f
    );

    TestEqual(
        TEXT("HP Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        70.f
    );

    AttributeComponent->DecreaseStatBase(
        EP3R_StatType::SP,
        15.f
    );

    TestEqual(
        TEXT("SP Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        25.f
    );


    // =========================================================
    // 5. Underflow / Overflow
    // =========================================================

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        -FLT_MAX
    );

    TestEqual(
        TEXT("HP Underflow"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        0.f
    );

    TestEqual(
        TEXT("HP Base Underflow"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        0.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        FLT_MAX
    );

    TestEqual(
        TEXT("HP Overflow"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        100.f
    );

    TestEqual(
        TEXT("HP Base Overflow"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        100.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::SP,
        -FLT_MAX
    );

    TestEqual(
        TEXT("SP Underflow"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        0.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::SP,
        FLT_MAX
    );

    TestEqual(
        TEXT("SP Overflow"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        50.f
    );


    // =========================================================
    // 6. MaxHP / MaxSP Minimum
    // =========================================================

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxHP,
        0.f
    );

    TestEqual(
        TEXT("MaxHP Minimum Clamp"),
        AttributeComponent->GetStat(EP3R_StatType::MaxHP),
        1.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxSP,
        -100.f
    );

    TestEqual(
        TEXT("MaxSP Minimum Clamp"),
        AttributeComponent->GetStat(EP3R_StatType::MaxSP),
        1.f
    );


    // =========================================================
    // 7. MaxHP Decrease -> HP Clamp
    // =========================================================

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxHP,
        100.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        80.f
    );

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxHP,
        50.f
    );

    TestEqual(
        TEXT("HP Clamped By MaxHP Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        50.f
    );

    TestEqual(
        TEXT("HP Base Clamped By MaxHP Decrease"),
        AttributeComponent->GetStatBase(EP3R_StatType::HP),
        50.f
    );

    TestEqual(
        TEXT("MaxHP After Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::MaxHP),
        50.f
    );

    TestEqual(
        TEXT("MaxHP Decrease Event Count"),
        Listener->Events.Num(),
        2
    );

    if (Listener->Events.Num() == 2)
    {
        TestEqual(
            TEXT("HP Clamp Event Type"),
            Listener->Events[0].StatType,
            EP3R_StatType::HP
        );

        TestEqual(
            TEXT("HP Clamp Event Value"),
            Listener->Events[0].Value,
            50.f
        );

        TestEqual(
            TEXT("MaxHP Event Type"),
            Listener->Events[1].StatType,
            EP3R_StatType::MaxHP
        );

        TestEqual(
            TEXT("MaxHP Event Value"),
            Listener->Events[1].Value,
            50.f
        );
    }


    // =========================================================
    // 8. MaxHP Increase -> HP Does Not Increase
    // =========================================================

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        40.f
    );

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxHP,
        100.f
    );

    TestEqual(
        TEXT("HP Does Not Increase With MaxHP"),
        AttributeComponent->GetStat(EP3R_StatType::HP),
        40.f
    );

    TestEqual(
        TEXT("MaxHP Increase"),
        AttributeComponent->GetStat(EP3R_StatType::MaxHP),
        100.f
    );

    TestEqual(
        TEXT("MaxHP Increase Event Count"),
        Listener->Events.Num(),
        1
    );


    // =========================================================
    // 9. MaxSP Decrease -> SP Clamp
    // =========================================================

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxSP,
        100.f
    );

    AttributeComponent->SetStatBase(
        EP3R_StatType::SP,
        80.f
    );

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::MaxSP,
        30.f
    );

    TestEqual(
        TEXT("SP Clamped By MaxSP Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::SP),
        30.f
    );

    TestEqual(
        TEXT("SP Base Clamped By MaxSP Decrease"),
        AttributeComponent->GetStatBase(EP3R_StatType::SP),
        30.f
    );

    TestEqual(
        TEXT("MaxSP After Decrease"),
        AttributeComponent->GetStat(EP3R_StatType::MaxSP),
        30.f
    );

    TestEqual(
        TEXT("MaxSP Decrease Event Count"),
        Listener->Events.Num(),
        2
    );

    if (Listener->Events.Num() == 2)
    {
        TestEqual(
            TEXT("SP Clamp Event Type"),
            Listener->Events[0].StatType,
            EP3R_StatType::SP
        );

        TestEqual(
            TEXT("SP Clamp Event Value"),
            Listener->Events[0].Value,
            30.f
        );

        TestEqual(
            TEXT("MaxSP Event Type"),
            Listener->Events[1].StatType,
            EP3R_StatType::MaxSP
        );

        TestEqual(
            TEXT("MaxSP Event Value"),
            Listener->Events[1].Value,
            30.f
        );
    }


    // =========================================================
    // 10. Event Value / Type
    // =========================================================

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        25.f
    );

    TestEqual(
        TEXT("HP Event Count"),
        Listener->Events.Num(),
        1
    );

    if (Listener->Events.Num() == 1)
    {
        TestEqual(
            TEXT("HP Event Type"),
            Listener->Events[0].StatType,
            EP3R_StatType::HP
        );

        TestEqual(
            TEXT("HP Event Value"),
            Listener->Events[0].Value,
            25.f
        );
    }


    // =========================================================
    // 11. Remove Listener
    // =========================================================

    AttributeComponent->RemoveStatListener(
        EP3R_StatType::HP,
        HPHandle
    );

    Listener->ClearEvents();

    AttributeComponent->SetStatBase(
        EP3R_StatType::HP,
        10.f
    );

    TestEqual(
        TEXT("Removed HP Listener Is Not Called"),
        Listener->Events.Num(),
        0
    );


    // =========================================================
    // Cleanup
    // =========================================================

    AttributeComponent->RemoveStatListener(
        EP3R_StatType::MaxHP,
        MaxHPHandle
    );

    AttributeComponent->RemoveStatListener(
        EP3R_StatType::SP,
        SPHandle
    );

    AttributeComponent->RemoveStatListener(
        EP3R_StatType::MaxSP,
        MaxSPHandle
    );

    return true;
}
