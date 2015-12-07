// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Engine.h"
#include "FuzzytotemsAugmenterBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UENUM(BlueprintType)
enum class ESortType : uint8
{
	EST_Sort			UMETA(DisplayName="Default (Stable Sort)"),
	EST_UnstableSort	UMETA(DisplayName="Unstable Sort"),
	EST_HeapSort		UMETA(DisplayName="Heap Sort"),

	EST_MAX				UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EErrorCode : uint8
{
	EEC_NoError			UMETA(DisplayName = "No Error"),
	EEC_NoInterface		UMETA(DisplayName = "No ISortable interface detected"),
	EEC_Exception		UMETA(DisplayName = "An exception was thrown; Will not retain output"),

	EEC_MAX				UMETA(Hidden)
};

UCLASS()
class UFuzzytotemsAugmenterBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort Float TArray", Keywords = "FuzzytotemsAugmenter TArray Sort Float"), Category = "Fuzzytotems TArray")
		static bool TArraySortFloat(TArray<float> input, TArray<float> &output, ESortType optionalSetting);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort Int TArray", Keywords = "FuzzytotemsAugmenter TArray Sort Int"), Category = "Fuzzytotems TArray")
		static bool TArraySortInt(TArray<int32> input, TArray<int32> &output, ESortType optionalSetting);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort String TArray", Keywords = "FuzzytotemsAugmenter TArray Sort FString"), Category = "Fuzzytotems TArray")
		static bool TArraySortString(TArray<FString> input, TArray<FString> &output, ESortType optionalSetting);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort Name TArray", Keywords = "FuzzytotemsAugmenter TArray Sort FName"), Category = "Fuzzytotems TArray")
		static bool TArraySortName(TArray<FName> input, TArray<FName> &output, ESortType optionalSetting);
	//UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort Text TArray", Keywords = "FuzzytotemsAugmenter TArray Sort FText"), Category = "Fuzzytotems TArray")
	//	static bool TArraySortText(TArray<FText> input, TArray<FText> &output, ESortType optionalSetting);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Sort Object TArray", Keywords = "FuzzytotemsAugmenter TArray Sort Object"), Category = "Fuzzytotems TArray")
		static bool TArraySortObject(TArray<UObject*> input, TArray<UObject*> &output, ESortType optionalSetting);

	template<typename t>
	static bool InternalPrimitiveSort(TArray<t> input, TArray<t> &output, ESortType setting);

	static bool InternalObjectSort(TArray<UObject*> input, TArray<UObject*> &output, ESortType setting);

	static bool Comparison(const UObject lefthand, const UObject righthand);
};

UINTERFACE(MinimalAPI)
class UISortable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IISortable
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Sorting Predicate", Keywords = "Sorting Predicate"), Category = "Fuzzytotems TArray")
		bool Compare(const UObject* otherObject);
};

UCLASS(Blueprintable)
class UQueueWrapper : public UObject
{
	GENERATED_UCLASS_BODY()

private:
	TQueue<UObject*> mQueue;

private:
	bool enforceSameClass;
	TSubclassOf<UObject> enforcedClass;

public:
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enforce Same Class", Keywords = "Queue Enforce Same Class Matching Restrict"), Category = "Fuzzytotems TQueue")
		void SetEnforceSameClass(bool isEnforcing);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enforced Class", Keywords = "Queue Enforced Class"), Category = "Fuzzytotems TQueue")
		void SetEnforcedClass(TSubclassOf<UObject> classToEnforce);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Enqueue", Keywords = "Enqueue Add Queue Insert Head Push Emplace +"), Category = "Fuzzytotems TQueue")
		bool Enqueue(UObject* itemToEnqueue);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Dequeue", Keywords = "Dequeue Remove Queue Tail Pop Remove -"), Category = "Fuzzytotems TQueue")
		bool Dequeue(UObject*& outItem);
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is Empty", Keywords = "Queue Contains Empty IsEmpty Zero Blank"), Category = "Fuzzytotems TQueue")
		bool IsEmpty();
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Peek", Keywords = "Queue Peek First Top Tail Look"), Category = "Fuzzytotems TQueue")
		bool Peek(UObject*& peekItem);
};

UCLASS()
class UStackWrapper : public UObject
{
	GENERATED_UCLASS_BODY()
};

UCLASS()
class UPriorityQueueWrapper : public UObject
{
	GENERATED_UCLASS_BODY()
};

//UCLASS()
//class UMapWrapper : public UObject
//{
//	GENERATED_UCLASS_BODY()
//};
//
//UCLASS()
//class UMultiMapWrapper : public UObject
//{
//	GENERATED_UCLASS_BODY()
//};
//
//UCLASS()
//class USetWrapper : public UObject
//{
//	GENERATED_UCLASS_BODY()
//};
//
//UCLASS()
//class UMultiSetWrapper : public UObject
//{
//	GENERATED_UCLASS_BODY()
//};
//
//UCLASS()
//class UTextWriter : public UObject
//{
//	GENERATED_UCLASS_BODY()
//};