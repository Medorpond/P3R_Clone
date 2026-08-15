#if WITH_DEV_AUTOMATION_TESTS

#include "StatComponentTestMocks.h"
#include "Character/StatComponents/SPComponent.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(SPComponentTest, "P3R_Clone.P3R_Clone.Private.Test.Character.StatComponents.SPComponentTest",
                                 EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool SPComponentTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
    
    // TODO: This is a rough test. There is room for improvement later.
    
    // TestCondition
    
    // Note: Set within the allowed range of SPComponent
    const float InitMaxSP = 100.f;
    
    // Note: Set within the allowed range of SPComponent, less than or equal to MaxSP
    const float InitSP = 90.f;
    
    // Setup
    UWorld* TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
    FWorldContext& WordContext = GEngine->CreateNewWorldContext(EWorldType::Game);
    WordContext.SetCurrentWorld(TestWorld);
    
    AActor* DummyActor = TestWorld->SpawnActor<AActor>();
    
    auto* SPComp = NewObject<USPComponent>(DummyActor);
    
    SPComp->RegisterComponent();
    
    UStatTestListener* SPListener = NewObject<UStatTestListener>(TestWorld);
    UStatTestListener* MaxSPListener = NewObject<UStatTestListener>(TestWorld);
    
    SPComp->OnSPChanged.AddDynamic(SPListener, &UStatTestListener::HandleStatChange);
    SPComp->OnMaxSPChanged.AddDynamic(MaxSPListener, &UStatTestListener::HandleStatChange);
    
    // TEST
    
    // Initialization
    SPComp->OverwriteMaxSP(InitMaxSP); 
    SPComp->OverwriteSP(InitSP);
    
    // Compare the actual stored value with the injected value
    TestEqual(TEXT("Overwritten MaxSP does not match actual value"), SPComp->GetMaxSP(), InitMaxSP);
    TestEqual(TEXT("Overwritten SP does not match actual value"), SPComp->GetSP(), InitSP);
    
    // Check broadcast reception and compare the injected value with the broadcasted value
    TestTrue(TEXT("SP Not Broadcasted"), SPListener->bWasCalled);
    TestEqual(TEXT("Broadcasted SP does not match expected value"), SPListener->ReceivedValue, InitSP);
    
    TestTrue(TEXT("Max SP Not Broadcasted"), MaxSPListener->bWasCalled);
    TestEqual(TEXT("Broadcasted Max SP does not match expected value"), MaxSPListener->ReceivedValue, InitMaxSP);
    
    SPListener->Reset();
    MaxSPListener->Reset();
    
    
    // Overflow guard
    // Note: Test against all upper limits defined in HealthComponent.
    const float OverflowValue = SPComp->GetMaxSP() + 10.f;
    
    SPComp->OverwriteSP(OverflowValue);
    
    // Compare max SP with current health
    TestEqual(TEXT("SP Overflow"), SPComp->GetSP(), SPComp->GetMaxSP());
    
    // Compare the broadcasted value with current SP. [Note] This might be true if Max Health and Current Health don't match. Evaluate comprehensively.
    TestEqual(TEXT("Broadcasted SP not clamped"), SPListener->ReceivedValue, SPComp->GetMaxSP());
    
    SPListener->Reset();
    
    // Underflow guard
    // Note: Test against all lower limits defined in HealthComponent.
    float UnderflowValue = -1.f;
    
    SPComp->OverwriteSP(UnderflowValue);
    SPComp->OverwriteMaxSP(UnderflowValue);
    
    // Compare the actual value with the lower limit. [Note]: Reference as a variable if the lower limit is design-variable
    TestEqual(TEXT("Max SP underflow"), SPComp->GetMaxSP(), 1.f);
    TestEqual(TEXT("SP Underflow"), SPComp->GetSP(), 0.f);
    
    TestEqual(TEXT("Broadcasted MaxSP not Clamped"), MaxSPListener->ReceivedValue, 1.f);
    TestEqual(TEXT("Broadcasted SP not Clamped"), SPListener->ReceivedValue, 0.f);
    
    
    // Decrease test
    float ExpectedValue = 100.f;
    SPComp->OverwriteMaxSP(ExpectedValue);
    SPComp->OverwriteSP(ExpectedValue);
    
    SPListener->Reset();
    MaxSPListener->Reset();
    
    const float StepSize = 10.f;
    int32 RequiredLoop = FMath::CeilToInt32(SPComp->GetSP() / StepSize);
    
    for (int32 i = 0; i < RequiredLoop; ++i)
    {
       SPComp->DecreaseSP(StepSize);
       ExpectedValue = FMath::Max(ExpectedValue-StepSize, 0.f);
       
       // Compare expected value with internal value
       TestEqual(TEXT("Decreased HP does not match expected value"), SPComp->GetSP(), ExpectedValue);
       
       // Compare expected value with broadcasted value
       TestEqual(TEXT("Broadcasted Decreased HP does not match expected value"), SPListener->ReceivedValue, ExpectedValue);
    }
    
    // Increase test
    ExpectedValue = 0.f;
    SPComp->OverwriteSP(ExpectedValue);
    SPListener->Reset();
    
    RequiredLoop = FMath::CeilToInt32(SPComp->GetMaxSP() / StepSize);
    
    for (int32 i = 0; i < RequiredLoop; ++i)
    {
       SPComp->IncreaseSP(StepSize);
       ExpectedValue = FMath::Min(ExpectedValue + StepSize, SPComp->GetMaxSP());
       
       // Compare expected value with internal value
       TestEqual(TEXT("Increased SP does not match expected value"), SPComp->GetSP(), ExpectedValue);
       
       // Compare expected value with broadcasted value
       TestEqual(TEXT("Increased Broadcasted SP does not match expected value"), SPListener->ReceivedValue, ExpectedValue);
    }
    
    // Check if it matches max health on full recover
    TestEqual(TEXT("HP does not match Max HP on full recover"), SPComp->GetSP(), SPComp->GetMaxSP());
    
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
