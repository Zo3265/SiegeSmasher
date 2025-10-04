// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SiegeSmasher/WaveGen/SpawnPoint.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSpawnPoint() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
SIEGESMASHER_API UClass* Z_Construct_UClass_ASpawnPoint();
SIEGESMASHER_API UClass* Z_Construct_UClass_ASpawnPoint_NoRegister();
UPackage* Z_Construct_UPackage__Script_SiegeSmasher();
// End Cross Module References

// Begin Class ASpawnPoint
void ASpawnPoint::StaticRegisterNativesASpawnPoint()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(ASpawnPoint);
UClass* Z_Construct_UClass_ASpawnPoint_NoRegister()
{
	return ASpawnPoint::StaticClass();
}
struct Z_Construct_UClass_ASpawnPoint_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "WaveGen/SpawnPoint.h" },
		{ "ModuleRelativePath", "WaveGen/SpawnPoint.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AllocatedSpawnTimeMin_MetaData[] = {
		{ "Category", "SpawnPoint" },
		{ "ModuleRelativePath", "WaveGen/SpawnPoint.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AllocatedSpawnTimeMax_MetaData[] = {
		{ "Category", "SpawnPoint" },
		{ "ModuleRelativePath", "WaveGen/SpawnPoint.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoolDownTimerMin_MetaData[] = {
		{ "Category", "SpawnPoint" },
		{ "ModuleRelativePath", "WaveGen/SpawnPoint.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CoolDownTimerMax_MetaData[] = {
		{ "Category", "SpawnPoint" },
		{ "ModuleRelativePath", "WaveGen/SpawnPoint.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AllocatedSpawnTimeMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AllocatedSpawnTimeMax;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CoolDownTimerMin;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CoolDownTimerMax;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASpawnPoint>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpawnPoint_Statics::NewProp_AllocatedSpawnTimeMin = { "AllocatedSpawnTimeMin", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpawnPoint, AllocatedSpawnTimeMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AllocatedSpawnTimeMin_MetaData), NewProp_AllocatedSpawnTimeMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpawnPoint_Statics::NewProp_AllocatedSpawnTimeMax = { "AllocatedSpawnTimeMax", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpawnPoint, AllocatedSpawnTimeMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AllocatedSpawnTimeMax_MetaData), NewProp_AllocatedSpawnTimeMax_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpawnPoint_Statics::NewProp_CoolDownTimerMin = { "CoolDownTimerMin", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpawnPoint, CoolDownTimerMin), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoolDownTimerMin_MetaData), NewProp_CoolDownTimerMin_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASpawnPoint_Statics::NewProp_CoolDownTimerMax = { "CoolDownTimerMax", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASpawnPoint, CoolDownTimerMax), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CoolDownTimerMax_MetaData), NewProp_CoolDownTimerMax_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASpawnPoint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpawnPoint_Statics::NewProp_AllocatedSpawnTimeMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpawnPoint_Statics::NewProp_AllocatedSpawnTimeMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpawnPoint_Statics::NewProp_CoolDownTimerMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASpawnPoint_Statics::NewProp_CoolDownTimerMax,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASpawnPoint_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASpawnPoint_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_SiegeSmasher,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASpawnPoint_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASpawnPoint_Statics::ClassParams = {
	&ASpawnPoint::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASpawnPoint_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASpawnPoint_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASpawnPoint_Statics::Class_MetaDataParams), Z_Construct_UClass_ASpawnPoint_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASpawnPoint()
{
	if (!Z_Registration_Info_UClass_ASpawnPoint.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASpawnPoint.OuterSingleton, Z_Construct_UClass_ASpawnPoint_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASpawnPoint.OuterSingleton;
}
template<> SIEGESMASHER_API UClass* StaticClass<ASpawnPoint>()
{
	return ASpawnPoint::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASpawnPoint);
ASpawnPoint::~ASpawnPoint() {}
// End Class ASpawnPoint

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_SpawnPoint_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASpawnPoint, ASpawnPoint::StaticClass, TEXT("ASpawnPoint"), &Z_Registration_Info_UClass_ASpawnPoint, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASpawnPoint), 2646406027U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_SpawnPoint_h_1014670865(TEXT("/Script/SiegeSmasher"),
	Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_SpawnPoint_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_richa_OneDrive_Desktop_SiegeSmasher_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_SpawnPoint_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
