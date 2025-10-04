// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SiegeSmasher/Enemies/EnemyInheritTest1.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyInheritTest1() {}

// Begin Cross Module References
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyBase();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyInheritTest1();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyInheritTest1_NoRegister();
UPackage* Z_Construct_UPackage__Script_SiegeSmasher();
// End Cross Module References

// Begin Class AEnemyInheritTest1
void AEnemyInheritTest1::StaticRegisterNativesAEnemyInheritTest1()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyInheritTest1);
UClass* Z_Construct_UClass_AEnemyInheritTest1_NoRegister()
{
	return AEnemyInheritTest1::StaticClass();
}
struct Z_Construct_UClass_AEnemyInheritTest1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Enemies/EnemyInheritTest1.h" },
		{ "ModuleRelativePath", "Enemies/EnemyInheritTest1.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyInheritTest1>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AEnemyInheritTest1_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AEnemyBase,
	(UObject* (*)())Z_Construct_UPackage__Script_SiegeSmasher,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyInheritTest1_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyInheritTest1_Statics::ClassParams = {
	&AEnemyInheritTest1::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyInheritTest1_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyInheritTest1_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyInheritTest1()
{
	if (!Z_Registration_Info_UClass_AEnemyInheritTest1.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyInheritTest1.OuterSingleton, Z_Construct_UClass_AEnemyInheritTest1_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyInheritTest1.OuterSingleton;
}
template<> SIEGESMASHER_API UClass* StaticClass<AEnemyInheritTest1>()
{
	return AEnemyInheritTest1::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyInheritTest1);
AEnemyInheritTest1::~AEnemyInheritTest1() {}
// End Class AEnemyInheritTest1

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest1_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyInheritTest1, AEnemyInheritTest1::StaticClass, TEXT("AEnemyInheritTest1"), &Z_Registration_Info_UClass_AEnemyInheritTest1, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyInheritTest1), 2787431458U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest1_h_3033469106(TEXT("/Script/SiegeSmasher"),
	Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest1_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyInheritTest1_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
