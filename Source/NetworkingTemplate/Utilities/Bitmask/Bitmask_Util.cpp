// Parent Header
#include "Bitmask_Util.h"

// Unreal
#include "Engine/Engine.h"


// Public
bool UBitmask_Util::IsEqual_Pure(int32 _bitmaskToCheck, int32 _bitsToCheckFor)
{
	if (_bitmaskToCheck == _bitsToCheckFor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UBitmask_Util::IsSet_Pure(int32 _bitmaskToCheck, int32 _bitsToCheckFor)
{
	int32 tempBitmask = _bitmaskToCheck & _bitsToCheckFor;

	if (_bitmaskToCheck == tempBitmask)
	{
		return true;
	}
	else
	{
		return false;
	}

}

int32 UBitmask_Util::Set_Pure(int32 _bitmaskToSet, int32 _bitsToAdd)
{
	int32 result = _bitmaskToSet | _bitsToAdd;

	return result;
}

int32 UBitmask_Util::Remove_Pure(int32 _bitmaskToSet, int32 _bitsToRemove)
{
	int32 result = !_bitsToRemove & _bitmaskToSet;

	return result;
}

void UBitmask_Util::IsEqual(EIsResult& _execRoute, int32 _bitmaskToCheck, int32 _bitsToCheckFor)
{
	if (_bitmaskToCheck == _bitsToCheckFor)
	{
		_execRoute = EIsResult::Yes;
	}
	else
	{
		_execRoute = EIsResult::No;
	}
}

void UBitmask_Util::IsSet(EIsResult& _execRoute, int32 _bitmaskToCheck, int32 _bitsToCheckFor)
{
	if (IsSet_Pure(_bitmaskToCheck, _bitsToCheckFor))
	{
		_execRoute = EIsResult::Yes;
	}
	else
	{
		_execRoute = EIsResult::No;
	}
}

void UBitmask_Util::Set(int32& _bitmaskToSet, int32 _bitsToAdd)
{
	_bitmaskToSet = Set_Pure(_bitmaskToSet, _bitsToAdd);
}

void UBitmask_Util::Remove(int32& _bitmaskToSet, int32 _bitsToRemove)
{
	_bitmaskToSet = Remove_Pure(_bitmaskToSet, _bitsToRemove);
}
