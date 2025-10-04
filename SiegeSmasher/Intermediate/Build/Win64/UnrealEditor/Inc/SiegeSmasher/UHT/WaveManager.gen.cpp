// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SiegeSmasher/WaveGen/WaveManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWaveManager() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AActor();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();
SIEGESMASHER_API UClass* Z_Construct_UClass_ASpawnPoint_NoRegister();
SIEGESMASHER_API UClass* Z_Construct_UClass_AWaveManager();
SIEGESMASHER_API UClass* Z_Construct_UClass_AWaveManager_NoRegister();
UPackage* Z_Construct_UPackage__Script_SiegeSmasher();
// End Cross Module References

// Begin Class AWaveManager
void AWaveManager::StaticRegisterNativesAWaveManager()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AWaveManager);
UClass* Z_Construct_UClass_AWaveManager_NoRegister()
{
	return AWaveManager::StaticClass();
}
struct Z_Construct_UClass_AWaveManager_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "WaveGen/WaveManager.h" },
		{ "ModuleRelativePath", "WaveGen/WaveManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EnemiesToSpawn_MetaData[] = {
		{ "Category", "EnemiesToSpawn" },
		{ "ModuleRelativePath", "WaveGen/WaveManager.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnPoints_MetaData[] = {
		{ "Category", "WaveSpawnPoints" },
		{ "ModuleRelativePath", "WaveGen/WaveManager.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_EnemiesToSpawn_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_EnemiesToSpawn;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_SpawnPoints_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SpawnPoints;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AWaveManager>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWaveManager_Statics::NewProp_EnemiesToSpawn_Inner = { "EnemiesToSpawn", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_AEnemyBase_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AWaveManager_Statics::NewProp_EnemiesToSpawn = { "EnemiesToSpawn", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaveManager, EnemiesToSpawn), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EnemiesToSpawn_MetaData), NewProp_EnemiesToSpawn_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AWaveManager_Statics::NewProp_SpawnPoints_Inner = { "SpawnPoints", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_ASpawnPoint_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AWaveManager_Statics::NewProp_SpawnPoints = { "SpawnPoints", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AWaveManager, SpawnPoints), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnPoints_MetaData), NewProp_SpawnPoints_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AWaveManager_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaveManager_Statics::NewProp_EnemiesToSpawn_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaveManager_Statics::NewProp_EnemiesToSpawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaveManager_Statics::NewProp_SpawnPoints_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AWaveManager_Statics::NewProp_SpawnPoints,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaveManager_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AWaveManager_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AActor,
	(UObject* (*)())Z_Construct_UPackage__Script_SiegeSmasher,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AWaveManager_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AWaveManager_Statics::ClassParams = {
	&AWaveManager::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AWaveManager_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AWaveManager_Statics::PropPointers),
	0,
	0x009000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AWaveManager_Statics::Class_MetaDataParams), Z_Construct_UClass_AWaveManager_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AWaveManager()
{
	if (!Z_Registration_Info_UClass_AWaveManager.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AWaveManager.OuterSingleton, Z_Construct_UClass_AWaveManager_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AWaveManager.OuterSingleton;
}
template<> SIEGESMASHER_API UClass* StaticClass<AWaveManager>()
{
	return AWaveManager::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AWaveManager);
AWaveManager::~AWaveManager() {}
// End Class AWaveManager

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_WaveManager_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AWaveManager, AWaveManager::StaticClass, TEXT("AWaveManager"), &Z_Registration_Info_UClass_AWaveManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AWaveManager), 1025521711U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_WaveManager_h_1803647066(TEXT("/Script/SiegeSmasher"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_WaveManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_WaveGen_WaveManager_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
