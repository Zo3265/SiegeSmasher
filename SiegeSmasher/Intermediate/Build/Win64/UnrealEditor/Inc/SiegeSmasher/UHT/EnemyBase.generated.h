// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "Enemies/EnemyBase.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef SIEGESMASHER_EnemyBase_generated_h
#error "EnemyBase.generated.h already included, missing '#pragma once' in EnemyBase.h"
#endif
#define SIEGESMASHER_EnemyBase_generated_h

#define FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_23_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAEnemyBase(); \
	friend struct Z_Construct_UClass_AEnemyBase_Statics; \
public: \
	DECLARE_CLASS(AEnemyBase, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SiegeSmasher"), NO_API) \
	DECLARE_SERIALIZER(AEnemyBase)


#define FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_23_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AEnemyBase(AEnemyBase&&); \
	AEnemyBase(const AEnemyBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AEnemyBase); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AEnemyBase); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AEnemyBase) \
	NO_API virtual ~AEnemyBase();


#define FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_19_PROLOG
#define FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_23_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_23_INCLASS_NO_PURE_DECLS \
	FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h_23_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SIEGESMASHER_API UClass* StaticClass<class AEnemyBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Users_kewin_Desktop_C__Unreal_Engine_Assigment_SiegeSmasher_SiegeSmasher_Source_SiegeSmasher_Enemies_EnemyBase_h


#define FOREACH_ENUM_ENEMYTYPES(op) \
	op(BASE) \
	op(BASE1) 
PRAGMA_ENABLE_DEPRECATION_WARNINGS
