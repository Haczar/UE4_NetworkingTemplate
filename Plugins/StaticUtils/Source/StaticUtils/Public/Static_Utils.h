// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

// Unreal
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

// UHeader Tool
#include "Static_Utils.generated.h"



// Enum

UENUM(BlueprintType)
enum class EContinue : uint8
{
	Continue,
	_
};

UENUM(BlueprintType)
enum class EIsResult : uint8
{
	Yes,
	No
};



/**
*
*/
UCLASS(Blueprintable)
class STATICUTILS_API UStatic_Utils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// Comile-time constants.
	struct CT 
	{
		// Timing

		static constexpr float Clock_24Hz  = 1.0f / 24.0f;
		static constexpr float Clock_30Hz  = 1.0f / 30.0f;
		static constexpr float Clock_42Hz  = 1.0f / 42.0f;
		static constexpr float Clock_45Hz  = 1.0f / 45.0f;
		static constexpr float Clock_50Hz  = 1.0f / 50.0f;
		static constexpr float Clock_60Hz  = 1.0f / 60.0f;
		static constexpr float Clock_72Hz  = 1.0f / 70.0f;
		static constexpr float Clock_80Hz  = 1.0f / 80.0f;
		static constexpr float Clock_90Hz  = 1.0f / 90.0f;
		static constexpr float Clock_100Hz = 1.0f / 100.0f;
		static constexpr float Clock_120Hz = 1.0f / 120.0f;
		static constexpr float Clock_240Hz = 1.0f / 240.0f;
		static constexpr float Clock_480Hz = 1.0f / 480.0f;
	};


	// Timing

	// Constant Rates

	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "24 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_24Hz () { return CT::Clock_24Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "30 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_30Hz () { return CT::Clock_30Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "42 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_42Hz () { return CT::Clock_42Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "50 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_50Hz () { return CT::Clock_50Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "60 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_60Hz () { return CT::Clock_60Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "72 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_72Hz () { return CT::Clock_72Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "80 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_80Hz () { return CT::Clock_80Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "90 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_90Hz () { return CT::Clock_90Hz;  }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "100 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_100Hz() { return CT::Clock_100Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "120 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_120Hz() { return CT::Clock_120Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "240 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_240Hz() { return CT::Clock_240Hz; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "480 Hz", CallableWithoutWorldContext))
	static FORCEINLINE float Clock_480Hz() { return CT::Clock_480Hz; }


	// Standard Timing

	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Time Rate",CallableWithoutWorldContext ))
	static FORCEINLINE float GetStd_Timerate        () { return timingRate_Std;        }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Quarter Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_Quarter() { return timingRate_Std / 4.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "Half Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_Half   () { return timingRate_Std / 2.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "2X Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_2X     () { return timingRate_Std * 2.0f; }
	UFUNCTION(BlueprintPure, Category = "Timing", Meta = (DisplayName = "4X Time Rate", CallableWithoutWorldContext))
	static FORCEINLINE float GetStd_Timerate_4X     () { return timingRate_Std * 2.0f; }

	UFUNCTION(BlueprintCallable, Category = "Timing", Meta = (DisplayName = "Set Time Rate"))
	static void Set_TimingRate_Std (float _rateDesired)
	{
		// Not the best check.. if inconsistency arises, use the a rigorous one.
		if (_rateDesired >= CT::Clock_24Hz)
		{
			timingRate_Std = _rateDesired;
		}
	};


private:

	static float timingRate_Std;
};
