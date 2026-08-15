#if WITH_DEV_AUTOMATION_TESTS

#include "StatComponentTestMocks.h"
#include "Misc/AutomationTest.h"
#include "System/Battle/StatComponents/HealthComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(HealthComponentTest, "P3R_Clone.P3R_Clone.Private.Test.Character.StatComponents.HealthComponentTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool HealthComponentTest::RunTest(const FString& Parameters)
{
    // Make the test pass by returning true, or fail by returning false.
    
    // TODO: This is a rough test. There is room for improvement later.
    
    // TestCondition
    
    // Note: Set within the allowed range of HealthComponent
    const float InitMaxHP = 100.f;
    
    // Note: Set within the allowed range of HealthComponent, less than or equal to MaxHP
    const float InitHP = 90.f;
    
    // Setup
    UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
    FWorldContext& WordContext = GEngine->CreateNewWorldContext(EWorldType::Game);
    WordContext.SetCurrentWorld(TestWorld);
    
    AActor* DummyActor = TestWorld->SpawnActor<AActor>();
    
    UHealthComponent* HealthComp = NewObject<UHealthComponent>(DummyActor);
    
    HealthComp->RegisterComponent();
    
    UStatTestListener* HealthListener = NewObject<UStatTestListener>(TestWorld);
    UStatTestListener* MaxHealthListener = NewObject<UStatTestListener>(TestWorld);
    UStatTestListener* HealthDepleteListener = NewObject<UStatTestListener>(TestWorld);
    
    HealthComp->OnHealthChanged.AddDynamic(HealthListener, &UStatTestListener::HandleStatChange);
    HealthComp->OnMaxHealthChanged.AddDynamic(MaxHealthListener, &UStatTestListener::HandleStatChange);
    HealthComp->OnHealthDepleted.AddDynamic(HealthDepleteListener, &UStatTestListener::HandleEventBroadcast);
    
    // TEST
    
    // Initialization
    HealthComp->OverwriteMaxHealth(InitMaxHP); 
    HealthComp->OverwriteHealth(InitHP);
    
    // Compare the actual stored value with the injected value
    TestEqual(TEXT("Overwritten MaxHP does not match actual value"), HealthComp->GetMaxHealth(), InitMaxHP);
    TestEqual(TEXT("Overwritten HP does not match actual value"), HealthComp->GetHealth(), InitHP);
    
    // Check broadcast reception and compare the injected value with the broadcasted value
    TestTrue(TEXT("HP Not Broadcasted"), HealthListener->bWasCalled);
    TestEqual(TEXT("Broadcasted HP does not match expected value"), HealthListener->ReceivedValue, InitHP);
    
    TestTrue(TEXT("Max HP Not Broadcasted"), MaxHealthListener->bWasCalled);
    TestEqual(TEXT("Broadcasted Max HP does not match expected value"), MaxHealthListener->ReceivedValue, InitMaxHP);
    
    HealthListener->Reset();
    MaxHealthListener->Reset();
    
    
    // Overflow guard
    // Note: Test against all upper limits defined in HealthComponent.
    const float OverflowValue = HealthComp->GetMaxHealth() + 10.f;
    
    HealthComp->OverwriteHealth(OverflowValue);
    
    // Compare max health with current health
    TestEqual(TEXT("HP Overflow"), HealthComp->GetHealth(), HealthComp->GetMaxHealth());
    
    // Compare the broadcasted value with current health. [Note] This might be true if Max Health and Current Health don't match. Evaluate comprehensively.
    TestEqual(TEXT("Broadcasted HP not clamped"), HealthListener->ReceivedValue, HealthComp->GetMaxHealth());
    
    HealthListener->Reset();
    
    // Underflow guard
    // Note: Test against all lower limits defined in HealthComponent.
    float UnderflowValue = -1.f;
    
    HealthComp->OverwriteHealth(UnderflowValue);
    HealthComp->OverwriteMaxHealth(UnderflowValue);
    
    // Compare the actual value with the lower limit. [Note]: Reference as a variable if the lower limit is design-variable
    TestEqual(TEXT("Max HP underflow"), HealthComp->GetMaxHealth(), 1.f);
    TestEqual(TEXT("HP Underflow"), HealthComp->GetHealth(), 0.f);
    
    TestEqual(TEXT("Broadcasted MaxHP not Clamped"), MaxHealthListener->ReceivedValue, 1.f);
    TestEqual(TEXT("Broadcasted HP not Clamped"), HealthListener->ReceivedValue, 0.f);
    
    
    // Decrease test
    float ExpectedValue = 100.f;
    HealthComp->OverwriteMaxHealth(ExpectedValue);
    HealthComp->OverwriteHealth(ExpectedValue);
    
    HealthListener->Reset();
    MaxHealthListener->Reset();
    
    const float StepSize = 10.f;
    int32 RequiredLoop = FMath::CeilToInt32(HealthComp->GetHealth() / StepSize);
    
    for (int32 i = 0; i < RequiredLoop; ++i)
    {
       HealthComp->DecreaseHealth(StepSize);
       ExpectedValue = FMath::Max(ExpectedValue-StepSize, 0.f);
       
       // Compare expected value with internal value
       TestEqual(TEXT("Decreased HP does not match expected value"), HealthComp->GetHealth(), ExpectedValue);
       
       // Compare expected value with broadcasted value
       TestEqual(TEXT("Broadcasted Decreased HP does not match expected value"), HealthListener->ReceivedValue, ExpectedValue);
    }
    
    // Check health depletion broadcast
    TestTrue(TEXT("HP Deplete event not called"), HealthDepleteListener->bWasCalled);
    HealthDepleteListener->Reset();
    
    // Increase test
    ExpectedValue = 0.f;
    HealthComp->OverwriteHealth(ExpectedValue);
    HealthListener->Reset();
    
    RequiredLoop = FMath::CeilToInt32(HealthComp->GetMaxHealth() / StepSize);
    
    for (int32 i = 0; i < RequiredLoop; ++i)
    {
       HealthComp->IncreaseHealth(StepSize);
       ExpectedValue = FMath::Min(ExpectedValue + StepSize, HealthComp->GetMaxHealth());
       
       // Compare expected value with internal value
       TestEqual(TEXT("Increased HP does not match expected value"), HealthComp->GetHealth(), ExpectedValue);
       
       // Compare expected value with broadcasted value
       TestEqual(TEXT("Increased Broadcasted HP does not match expected value"), HealthListener->ReceivedValue, ExpectedValue);
    }
    
    // Check if it matches max health on full recover
    TestEqual(TEXT("HP does not match Max HP on full recover"), HealthComp->GetHealth(), HealthComp->GetMaxHealth());
    
    // Clear
    
    if (DummyActor)
    {
       DummyActor->Destroy();
    }
    
    if (TestWorld)
    {
       GEngine->DestroyWorldContext(TestWorld);
       TestWorld->DestroyWorld(false);
    }
    
    return true;
}

#endif