// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SiegeSmasher/Enemies/EnemyBase.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEnemyBase() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyBase();
SIEGESMASHER_API UClass* Z_Construct_UClass_AEnemyBase_NoRegister();
SIEGESMASHER_API UEnum* Z_Construct_UEnum_SiegeSmasher_EnemyTypes();
UPackage* Z_Construct_UPackage__Script_SiegeSmasher();
// End Cross Module References

// Begin Enum EnemyTypes
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EnemyTypes;
static UEnum* EnemyTypes_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EnemyTypes.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EnemyTypes.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_SiegeSmasher_EnemyTypes, (UObject*)Z_Construct_UPackage__Script_SiegeSmasher(), TEXT("EnemyTypes"));
	}
	return Z_Registration_Info_UEnum_EnemyTypes.OuterSingleton;
}
template<> SIEGESMASHER_API UEnum* StaticEnum<EnemyTypes>()
{
	return EnemyTypes_StaticEnum();
}
struct Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BASE.Name", "BASE" },
		{ "BASE1.Name", "BASE1" },
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Enemies/EnemyBase.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "BASE", (int64)BASE },
		{ "BASE1", (int64)BASE1 },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_SiegeSmasher,
	nullptr,
	"EnemyTypes",
	"EnemyTypes",
	Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::Regular,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::Enum_MetaDataParams), Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_SiegeSmasher_EnemyTypes()
{
	if (!Z_Registration_Info_UEnum_EnemyTypes.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EnemyTypes.InnerSingleton, Z_Construct_UEnum_SiegeSmasher_EnemyTypes_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EnemyTypes.InnerSingleton;
}
// End Enum EnemyTypes

// Begin Class AEnemyBase
void AEnemyBase::StaticRegisterNativesAEnemyBase()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AEnemyBase);
UClass* Z_Construct_UClass_AEnemyBase_NoRegister()
{
	return AEnemyBase::StaticClass();
}
struct Z_Construct_UClass_AEnemyBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "Enemies/EnemyBase.h" },
		{ "ModuleRelativePath", "Enemies/EnemyBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEnemyBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AEnemyBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_SiegeSmasher,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AEnemyBase_Statics::ClassParams = {
	&AEnemyBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AEnemyBase_Statics::Class_MetaDataParams), Z_Construct_UClass_AEnemyBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AEnemyBase()
{
	if (!Z_Registration_Info_UClass_AEnemyBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AEnemyBase.OuterSingleton, Z_Construct_UClass_AEnemyBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AEnemyBase.OuterSingleton;
}
template<> SIEGESMASHER_API UClass* StaticClass<AEnemyBase>()
{
	return AEnemyBase::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AEnemyBase);
AEnemyBase::~AEnemyBase() {}
// End Class AEnemyBase

// Begin Registration
struct Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EnemyTypes_StaticEnum, TEXT("EnemyTypes"), &Z_Registration_Info_UEnum_EnemyTypes, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3297259468U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AEnemyBase, AEnemyBase::StaticClass, TEXT("AEnemyBase"), &Z_Registration_Info_UClass_AEnemyBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AEnemyBase), 2007567547U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_1422090497(TEXT("/Script/SiegeSmasher"),
	Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Unreal_Projects_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
