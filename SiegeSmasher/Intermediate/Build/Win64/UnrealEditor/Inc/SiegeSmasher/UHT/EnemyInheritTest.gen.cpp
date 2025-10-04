// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SiegeSmasher/Enemies/EnemyInheritTest.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyInheritTest() {}

// Begin Cross Module References
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyBase();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyInheritTest();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyInheritTest_NoRegister();
UPackage* Z_Construct_UPackage__Script_SiegeSmasher();
// End Cross Module References

// Begin Class AEnemyInheritTest
void AEnemyInheritTest::StaticRegisterNativesAEnemyInheritTest()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyInheritTest);
UClass* Z_Construct_UClass_AEnemyInheritTest_NoRegister()
{
	return AEnemyInheritTest::StaticClass();
}
struct Z_Construct_UClass_AEnemyInheritTest_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Enemies/EnemyInheritTest.h" },
		{ "ModuleRelativePath", "Enemies/EnemyInheritTest.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyInheritTest>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AEnemyInheritTest_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AEnemyBase,
	(UObject* (*)())Z_Construct_UPackage__Script_SiegeSmasher,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyInheritTest_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyInheritTest_Statics::ClassParams = {
	&AEnemyInheritTest::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyInheritTest_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyInheritTest_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyInheritTest()
{
	if (!Z_Registration_Info_UClass_AEnemyInheritTest.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyInheritTest.OuterSingleton, Z_Construct_UClass_AEnemyInheritTest_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyInheritTest.OuterSingleton;
}
template<> SIEGESMASHER_API UClass* StaticClass<AEnemyInheritTest>()
{
	return AEnemyInheritTest::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyInheritTest);
AEnemyInheritTest::~AEnemyInheritTest() {}
// End Class AEnemyInheritTest

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyInheritTest, AEnemyInheritTest::StaticClass, TEXT("AEnemyInheritTest"), &Z_Registration_Info_UClass_AEnemyInheritTest, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyInheritTest), 3078361585U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest_h_365242992(TEXT("/Script/SiegeSmasher"),
	Z_CompiledInDeferFile_FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
