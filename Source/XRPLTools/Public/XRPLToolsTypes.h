#pragma once

#include "CoreMinimal.h"
#include "Json.h"

#include "XRPLToolsTypes.generated.h"


/**
 * Represents a callback structure for XRPL server responses.
 * This struct can be utilized in blueprints to handle responses 
 * from the XRPL server after making a request.
 */
USTRUCT(BlueprintType)
struct FXRPLResponseCallback
{
  GENERATED_BODY()

  FXRPLResponseCallback() {};

  FXRPLResponseCallback(UObject* BaseObject, const FName& FunctionName) :
    BaseObject(BaseObject),
    FunctionName(FunctionName)
  {
  };

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  UObject* BaseObject = nullptr;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  FName FunctionName;
};

/**
 * Enumerates the possible types of JSON values.
 * This allows for distinguishing between various data types
 * found within a JSON payload, such as strings, numbers, objects, arrays, etc.
 */
UENUM(BlueprintType)
enum class EJsonValueType : uint8
{
  Null,
  Boolean,
  NumberInt,
  NumberFloat,
  String,
  Array,
  Object
};

/**
 * Represents a variant data type that can hold various types of JSON values.
 * The variant is used in scenarios where the exact type of data
 * might be unknown at compile time and can vary during runtime.
 */
USTRUCT(BlueprintType)
struct FJsonDynamicVariant
{
  GENERATED_BODY()

  // Values for possible JSON types
  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  bool BooleanValue;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  int32 IntValue;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  float FloatValue;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  FString StringValue;
};

/**
 * Represents a more dynamic representation of a JSON value, suitable for blueprints.
 * This struct wraps around the FJsonDynamicVariant and offers methods
 * for accessing and manipulating the underlying data.
 */
USTRUCT(BlueprintType)
struct FJsonDynamicValue
{
  GENERATED_BODY()

  // Value Type
  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  EJsonValueType ValueType;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  FJsonDynamicVariant CurrentValue;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  TArray<FJsonDynamicVariant> ArrayValues;

  UPROPERTY(BlueprintReadWrite, Category = "XRPLedger")
  TMap<FString, FJsonDynamicVariant> ObjectValues;
};

/**
 * Represents the data structure for JSON responses from the XRPL server.
 * It provides a raw JSON string and also allows for on-demand
 * parsing into a structured representation.
 */
USTRUCT(BlueprintType)
struct FJsonResponseData
{
  GENERATED_BODY()

  // The raw JSON string response.
  UPROPERTY(BlueprintReadOnly, Category = "XRPLedger")
  FString RawJsonString;

  // A parsed version of the JSON string.
  // Note: This is mutable because we're lazily loading it.
  mutable TOptional<TMap<FString, FJsonDynamicValue>> ParsedJson;

  // Constructor
  FJsonResponseData() = default;
  FJsonResponseData(const FString& InRawJsonString) : RawJsonString(InRawJsonString) {}
};
