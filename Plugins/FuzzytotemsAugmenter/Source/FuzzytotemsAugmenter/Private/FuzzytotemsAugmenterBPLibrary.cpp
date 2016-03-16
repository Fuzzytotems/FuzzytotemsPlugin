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

//******************* End of BP Augmenter **************************
//******************* Start of Sortable Interface ******************

UISortable::UISortable(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

//******************* End of Sortable Interface ********************
//******************* Start of Queue Wrapper ***********************

UQueueWrapper::UQueueWrapper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UQueueWrapper::SetEnforceSameClass(bool isEnforcing)
{
	enforceSameClass = isEnforcing;
}

void UQueueWrapper::SetEnforcedClass(TSubclassOf<UObject> classToEnforce)
{
	enforcedClass = classToEnforce;
}

bool UQueueWrapper::Enqueue(UObject* itemToEnqueue)
{
	if (enforceSameClass)
	{
		if (itemToEnqueue->GetClass()->IsChildOf(enforcedClass))
		{
			return mQueue.Enqueue(itemToEnqueue);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return mQueue.Enqueue(itemToEnqueue);
	}
	
	return false; // How did you even get out here??
}

bool UQueueWrapper::Dequeue(UObject*& outItem)
{
	bool result = mQueue.Dequeue(outItem);
	return result;
}

bool UQueueWrapper::IsEmpty()
{
	return mQueue.IsEmpty();
}

bool UQueueWrapper::Peek(UObject*& peekItem)
{
	return (mQueue.Peek(peekItem));
}

//******************* End of Queue Wrapper *************************
//******************* Start of Sortable Interface ******************

UStackWrapper::UStackWrapper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

//******************* End of Stack Wrapper *************************
//******************* Start of Priority Queue Wrapper **************

UPriorityQueueWrapper::UPriorityQueueWrapper(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}