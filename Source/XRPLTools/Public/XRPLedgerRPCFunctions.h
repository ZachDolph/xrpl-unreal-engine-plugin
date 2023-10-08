#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XRPLToolsTypes.h"

#include "XRPLedgerRPCFunctions.generated.h"


/**
 * Provides a suite of blueprint-accessible functions to interact with 
 * the XRP Ledger (XRPL) via Remote Procedure Call (RPC) or WebSocket.
 * This class encapsulates the necessary functionality for constructing,
 * sending, and receiving data from the XRPL, with an emphasis on usability within blueprints.
 */
UCLASS()
class XRPLTOOLS_API UXRPLedgerRPCFunctions : public UBlueprintFunctionLibrary
{
  GENERATED_BODY()

public:

  /** Configures the plugin to use WebSocket communication. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static void SetUseWebsockets(bool UseWebsockets = false);

  /** Retrieves server information from the specified XRPL node. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static void ServerInfo(const FString& RequestURL, const FXRPLResponseCallback& ResponseCallback);

  /** Retrieves account information for the specified account address. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static void AccountInfo(const FString& RequestURL, const FString& AccountAddress, const FXRPLResponseCallback& ResponseCallback);

  /** Retrieves transaction information for the specified transaction hash. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static void TransactionInfo(const FString& RequestURL, const FString& TxHash, const FXRPLResponseCallback& ResponseCallback);

  /** Parses a JSON payload into a structured format. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static TMap<FString, FJsonDynamicValue> ParseJsonPayload(const FJsonResponseData& ResponseData);

  /** Beautifies a raw JSON string for improved readability. */
  UFUNCTION(BlueprintCallable, Category = "XRPLedger")
  static FString BeautifyJsonString(const FString& Payload);

private:

  /** Sends a JSON RPC request to the XRPL. */
  static void SendJsonRpcRequest(const FString& RequestUrl, const FString& MethodName, TArray<TSharedPtr<FJsonValue>>& ParamsArray, const FXRPLResponseCallback& ResponseCallback);

  /** Recursively parses a JSON value. */
  static FJsonDynamicValue ParseJsonValue(const TSharedPtr<FJsonValue>& JsonValue);

  /** Internal function to parse a JSON object payload. */
  static TMap<FString, FJsonDynamicValue> _ParseJsonPayload(TSharedPtr<FJsonObject> JsonObject);

private:

  /** Indicates whether to use WebSocket communication. */
  static bool bUseWebsockets;
};
