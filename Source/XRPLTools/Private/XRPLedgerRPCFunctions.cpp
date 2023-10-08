#include "XRPLedgerRPCFunctions.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"


bool UXRPLedgerRPCFunctions::bUseWebsockets = false;


/**
 * Sets whether the system should use Websockets for communication.
 *
 * @param UseWebsockets If true, the system will utilize Websockets.
 */
void UXRPLedgerRPCFunctions::SetUseWebsockets(bool UseWebsockets)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::SetUseWebsockets() -- %s"), UseWebsockets ? TEXT("True") : TEXT("False"));
  UXRPLedgerRPCFunctions::bUseWebsockets = UseWebsockets;

  // TO DO:
  // ADD CODE HERE TO HANDLE USING WEBSOCKETS OR NOT
}


/**
 * Requests server information from the specified XRPL server.
 *
 * @param RequestURL The URL of the XRPL server.
 * @param ResponseCallback The callback function to execute once the server responds.
 */
void UXRPLedgerRPCFunctions::ServerInfo(const FString& RequestURL, const FXRPLResponseCallback& ResponseCallback)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::ServerInfo()"));

  TArray<TSharedPtr<FJsonValue>> ParamsArray;

  SendJsonRpcRequest(RequestURL, TEXT("server_info"), ParamsArray, ResponseCallback);
}

/**
 * Requests account information for a given account address from the XRPL server.
 *
 * @param RequestURL The URL of the XRPL server.
 * @param AccountAddress The account address to query.
 * @param ResponseCallback The callback function to execute once the server responds.
 */
void UXRPLedgerRPCFunctions::AccountInfo(const FString& RequestURL, const FString& AccountAddress, const FXRPLResponseCallback& ResponseCallback)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::AccountInfo()"));

  TSharedPtr<FJsonObject> ParamObject = MakeShareable(new FJsonObject());
  ParamObject->SetStringField("account", AccountAddress);
  ParamObject->SetStringField("ledger_index", TEXT("current"));

  TArray<TSharedPtr<FJsonValue>> ParamsArray;
  ParamsArray.Add(MakeShareable(new FJsonValueObject(ParamObject)));

  SendJsonRpcRequest(RequestURL, TEXT("account_info"), ParamsArray, ResponseCallback);
}

/**
 * Requests transaction information for a given transaction hash from the XRPL server.
 *
 * @param RequestURL The URL of the XRPL server.
 * @param TxHash The transaction hash to query.
 * @param ResponseCallback The callback function to execute once the server responds.
 */
void UXRPLedgerRPCFunctions::TransactionInfo(const FString& RequestURL, const FString& TxHash, const FXRPLResponseCallback& ResponseCallback)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::TransactionInfo()"));

  TSharedPtr<FJsonObject> ParamObject = MakeShareable(new FJsonObject());
  ParamObject->SetStringField("transaction", TxHash);
  ParamObject->SetStringField("ledger_index", TEXT("current"));

  TArray<TSharedPtr<FJsonValue>> ParamsArray;
  ParamsArray.Add(MakeShareable(new FJsonValueObject(ParamObject)));

  SendJsonRpcRequest(RequestURL, TEXT("tx"), ParamsArray, ResponseCallback);
}

/**
 * Sends a JSON-RPC request to the specified URL with the provided method and parameters.
 *
 * @param RequestUrl The URL to send the JSON-RPC request to.
 * @param MethodName The method name for the JSON-RPC request.
 * @param ParamsArray The parameters for the JSON-RPC request.
 * @param ResponseCallback The callback function to execute once the server responds.
 */
void UXRPLedgerRPCFunctions::SendJsonRpcRequest(const FString& RequestUrl, const FString& MethodName, TArray<TSharedPtr<FJsonValue>>& ParamsArray, const FXRPLResponseCallback& ResponseCallback)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::SendJsonRpcRequest()"));

  // Create a new HTTP request
  TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();

  // Set the request URL
  HttpRequest->SetURL(RequestUrl);

  // Set the request method to POST
  HttpRequest->SetVerb(TEXT("POST"));

  // Set the content type header
  HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

  // Create the request payload
  TSharedPtr<FJsonObject> RequestPayload = MakeShareable(new FJsonObject());
  RequestPayload->SetStringField(TEXT("method"), MethodName);

  if (ParamsArray.Num())
  {
    RequestPayload->SetArrayField(TEXT("params"), ParamsArray);
  }

  // Convert the payload to a JSON string
  FString RequestString;
  TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestString);
  FJsonSerializer::Serialize(RequestPayload.ToSharedRef(), Writer);

  // Set the request body
  HttpRequest->SetContentAsString(RequestString);

  // Define the response callback
  HttpRequest->OnProcessRequestComplete().BindLambda([&, ResponseCallback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
  {
    UE_LOG(LogTemp, Warning, TEXT("HttpRequest->OnProcessRequestComplete()"));

    TSharedPtr<FJsonObject> JsonResponse = nullptr;
    if (bWasSuccessful && Response->GetResponseCode() == 200)
    {
      // Construct the FJsonResponseData using the raw response
      FJsonResponseData ResponseData(Response->GetContentAsString());
      
      // FIX ME:
      UE_LOG(LogTemp, Log, TEXT("Server Info Response: %s"), *ResponseData.RawJsonString);
      
      // Could check if the JSON is valid here by trying to parse it.
      // This step is optional since we're providing the lazy parsing mechanism.
      // It might make sense to skip this and let the user handle it with the GetParsedJson() function.
      
      // Call the provided callback function with the FJsonResponseData data
      if (ResponseCallback.BaseObject)
      {
        UFunction* FunctionToCall = ResponseCallback.BaseObject->FindFunctionChecked(ResponseCallback.FunctionName);
        if (FunctionToCall)
        {
          // Use the new struct for callback
          ResponseCallback.BaseObject->ProcessEvent(FunctionToCall, &ResponseData);
        }
        else
        {
          // Handle error, function not found!
          UE_LOG(LogTemp, Warning, TEXT("Function '%s' not found on target object %s!"), *ResponseCallback.FunctionName.ToString(), *ResponseCallback.BaseObject->GetName());
        }
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Failed to parse server_info JSON response or request failed."));
    }
  });

  // Send the request
  HttpRequest->ProcessRequest();
}

/**
 * Parses an FJsonValue into a more dynamic representation suitable for blueprints.
 *
 * @param JsonValue The FJsonValue to parse.
 * @return Returns a dynamic representation of the JSON value.
 */
FJsonDynamicValue UXRPLedgerRPCFunctions::ParseJsonValue(const TSharedPtr<FJsonValue>& JsonValue)
{
  UE_LOG(LogTemp, Warning, TEXT("UXRPLedgerRPCFunctions::ParseJsonValue()"));

  FJsonDynamicValue Result;

  switch (JsonValue->Type)
  {
    case EJson::Null:
    {
      Result.ValueType = EJsonValueType::Null;
      break;
    }
    case EJson::Boolean:
    {
      Result.ValueType = EJsonValueType::Boolean;
      Result.CurrentValue.BooleanValue = JsonValue->AsBool();
      break;
    }
    case EJson::Number:
    {
      if (FMath::FloorToDouble(JsonValue->AsNumber()) == JsonValue->AsNumber())
      {
        Result.ValueType = EJsonValueType::NumberInt;
        Result.CurrentValue.IntValue = static_cast<int32>(JsonValue->AsNumber());
      }
      else
      {
        Result.ValueType = EJsonValueType::NumberFloat;
        Result.CurrentValue.FloatValue = static_cast<float>(JsonValue->AsNumber());
      }
      break;
    }
    case EJson::String:
    {
      Result.ValueType = EJsonValueType::String;
      Result.CurrentValue.StringValue = JsonValue->AsString();
      break;
    }
    case EJson::Array:
    {
      Result.ValueType = EJsonValueType::Array;
      for (const auto& Element : JsonValue->AsArray())
      {
        Result.ArrayValues.Add(ParseJsonValue(Element).CurrentValue);
      }
      break;
    }
    case EJson::Object:
    {
      Result.ValueType = EJsonValueType::Object;
      for (const auto& Pair : JsonValue->AsObject()->Values)
      {
        Result.ObjectValues.Add(Pair.Key, ParseJsonValue(Pair.Value).CurrentValue);
      }
      break;
    }
    default:
    {
      // Do nothing for unknown types, the dynamic value remains in its default state
      break;
    }
  }

  return Result;
}

/**
 * Parses the JSON payload contained in the response data.
 *
 * @param ResponseData The response data containing the raw JSON string.
 * @return Returns a map representation of the parsed JSON data.
 */
TMap<FString, FJsonDynamicValue> UXRPLedgerRPCFunctions::ParseJsonPayload(const FJsonResponseData& ResponseData)
{
  // Check if we've already parsed the JSON.
  if (!ResponseData.ParsedJson.IsSet())
  {
    // If not, parse the RawJsonString and set the ParsedJson.
    TSharedPtr<FJsonObject> JsonObject;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseData.RawJsonString);
    if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
    {
      ResponseData.ParsedJson = _ParseJsonPayload(JsonObject);
    }
  }

  return ResponseData.ParsedJson.GetValue();
}

/**
 * Internally used function to parse an FJsonObject into a TMap representation.
 *
 * @param JsonObject The FJsonObject to parse.
 * @return Returns a map representation of the parsed JSON object.
 */
TMap<FString, FJsonDynamicValue> UXRPLedgerRPCFunctions::_ParseJsonPayload(TSharedPtr<FJsonObject> JsonObject)
{
  TMap<FString, FJsonDynamicValue> ResultMap;

  for (const auto& Pair : JsonObject->Values)
  {
    const FString& Key = Pair.Key;
    const TSharedPtr<FJsonValue>& Value = Pair.Value;

    // Parse the FJsonValue into our FJsonDynamicValue
    FJsonDynamicValue ParsedValue = ParseJsonValue(Value);

    // Add to our result map
    ResultMap.Add(Key, ParsedValue);
  }

  return ResultMap;
}

/**
 * Beautifies and formats a given JSON string.
 *
 * @param Payload The raw JSON string to beautify.
 * @return Returns a beautified version of the JSON string.
 */
FString UXRPLedgerRPCFunctions::BeautifyJsonString(const FString& Payload)
{
  // UE_LOG(LogTemp, Log, TEXT("%s"), *BeautifyJsonString(YourJsonPayloadString));
  TSharedPtr<FJsonObject> JsonObject;
  TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);

  if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
  {
    FString OutputString;
    TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&OutputString, 2);
    if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter))
    {
      return OutputString;
    }
  }

  // Return an empty string if something went wrong.
  return TEXT("");
}
