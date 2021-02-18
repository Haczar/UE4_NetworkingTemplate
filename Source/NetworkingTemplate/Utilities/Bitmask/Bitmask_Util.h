#pragma once

// Unreal
#include "CoreMinimal.h"

// NT
#include "Utilities/UStatic_Util.h"

// UHeader Tool
#include "Bitmask_Util.generated.h"



/**
*
*/
UCLASS(Blueprintable)
class NETWORKINGTEMPLATE_API UBitmask_Util : public UStatic_Util
{
	GENERATED_BODY()

public:

	//UFUNCTION(Category = "Bitmask", BlueprintCallable, BlueprintPure)

	UFUNCTION(Category = "Bitmask", BlueprintCallable, BlueprintPure) static bool  IsEqual_Pure(int32 BitmaskToCheck, int32 BitsToCheckFor);
	UFUNCTION(Category = "Bitmask", BlueprintCallable, BlueprintPure) static bool  IsSet_Pure  (int32 BitmaskToCheck, int32 BitsToCheckFor);
	UFUNCTION(Category = "Bitmask", BlueprintCallable, BlueprintPure) static int32 Set_Pure    (int32 BitmaskToSet  , int32 BitsToAdd     );
	UFUNCTION(Category = "Bitmask", BlueprintCallable, BlueprintPure) static int32 Remove_Pure (int32 BitmaskToSet  , int32 BitsToRemove  );

	//UFUNCTION(BlueprintCallable, Category = "Bitmask", Meta = (ExpandEnumAsExecs = "ExecRoute"))

	UFUNCTION(BlueprintCallable, Category = "Bitmask", Meta = (ExpandEnumAsExecs = "ExecRoute")) static void IsEqual(EIsResult& ExecRoute, int32 _bitmaskToCheck, int32 _bitsToCheckFor);
	UFUNCTION(BlueprintCallable, Category = "Bitmask", Meta = (ExpandEnumAsExecs = "ExecRoute")) static void IsSet  (EIsResult& ExecRoute, int32 _bitmaskToCheck, int32 _bitsToCheckFor);

	//UFUNCTION(Category = "Bitmask", BlueprintCallable)

	UFUNCTION(Category = "Bitmask", BlueprintCallable) static void Set   (UPARAM(ref) int32& BitmaskToSet, int32 BitsToAdd   );
	UFUNCTION(Category = "Bitmask", BlueprintCallable) static void Remove(UPARAM(ref) int32& BitmaskToSet, int32 BitsToRemove);
};
