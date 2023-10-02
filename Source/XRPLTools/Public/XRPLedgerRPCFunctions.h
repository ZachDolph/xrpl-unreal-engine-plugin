#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Json.h"
#include "UObject/Object.h"

#include "XRPLedgerRPCFunctions.generated.h"

typedef TFunction<void(TSharedPtr<FJsonObject>)> FJsonResponseCallback;


UCLASS()
class XRPLTOOLS_API UXRPLedgerRPCFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:

  static void ServerInfo(const FJsonResponseCallback& UserCallback);
  static void AccountInfo(const FString& AccountAddress, const FJsonResponseCallback& UserCallback);
  static void TransactionInfo(const FString& TxHash, const FJsonResponseCallback& UserCallback);

private:

  static void SendJsonRpcRequest(const FString& RequestUrl, const FString& MethodName, const TArray<TSharedPtr<FJsonValue>>& ParamsArray, const FJsonResponseCallback& UserCallback);
};
