// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "FuzzytotemsAugmenterPrivatePCH.h"
#include "FuzzytotemsAugmenterBPLibrary.h"

UFuzzytotemsAugmenterBPLibrary::UFuzzytotemsAugmenterBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UFuzzytotemsAugmenterBPLibrary::TArraySortFloat(TArray<float> input, TArray<float> &output, ESortType setting = ESortType::EST_Sort)
{
	return InternalPrimitiveSort<float>(input, output, setting);
}

bool UFuzzytotemsAugmenterBPLibrary::TArraySortInt(TArray<int32> input, TArray<int32> &output, ESortType setting = ESortType::EST_Sort)
{
	return InternalPrimitiveSort<int32>(input, output, setting);
}

bool UFuzzytotemsAugmenterBPLibrary::TArraySortString(TArray<FString> input, TArray<FString> &output, ESortType setting = ESortType::EST_Sort)
{
	return InternalPrimitiveSort<FString>(input, output, setting);
}

bool UFuzzytotemsAugmenterBPLibrary::TArraySortName(TArray<FName> input, TArray<FName> &output, ESortType setting = ESortType::EST_Sort)
{
	return InternalPrimitiveSort<FName>(input, output, setting);
}

//bool UFuzzytotemsAugmenterBPLibrary::TArraySortText(TArray<FText> input, TArray<FText> &output, ESortType setting = ESortType::EST_Sort)
//{
//	return InternalPrimitiveSort<FText>(input, output, setting);
//}

bool UFuzzytotemsAugmenterBPLibrary::TArraySortObject(TArray<UObject*> input, TArray<UObject*> &output, ESortType optionalSetting)
{
	return InternalObjectSort(input, output, optionalSetting);
}

template<typename t>
bool UFuzzytotemsAugmenterBPLibrary::InternalPrimitiveSort(TArray<t> input, TArray<t> &output, ESortType setting)
{
	switch (setting)
	{
	case ESortType::EST_UnstableSort:
		input.Sort();
		break;
	case ESortType::EST_HeapSort:
		input.HeapSort();
		break;
	case ESortType::EST_Sort:
	default:
		input.StableSort();
		break;
	}

	output = input;

	return true;
}

bool UFuzzytotemsAugmenterBPLibrary::InternalObjectSort(TArray<UObject*> input, TArray<UObject*> &output, ESortType setting)
{
	bool result = false;

	switch (setting)
	{
	case ESortType::EST_UnstableSort:
		//return IISortable::Execute_Compare(input[0], input[1]);
		//std::sort(0, input.Num(), ComparisonObj);
		input.Sort([](UObject& A, const UObject& B) { return IISortable::Execute_Compare(&A, &B);});
		result = true;
		//Sort(input[0], input.Num(), UFuzzytotemsAugmenterBPLibrary::Comparison);
		break;
	case ESortType::EST_HeapSort:
		//input.HeapSort([](UObject& A, const UObject& B) { return IISortable::Execute_Compare(&A, &B);});
		result = false;
		//input.HeapSort();
		break;
	case ESortType::EST_Sort:
		input.StableSort([](UObject& A, const UObject& B) { return IISortable::Execute_Compare(&A, &B);});
		result = true;
	default:
		//input.StableSort();
		break;
	}

	output = input;

	return result;
}

bool UFuzzytotemsAugmenterBPLibrary::Comparison(const UObject lefthand, const UObject righthand)
{
	return true;
}

UISortable::UISortable(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}