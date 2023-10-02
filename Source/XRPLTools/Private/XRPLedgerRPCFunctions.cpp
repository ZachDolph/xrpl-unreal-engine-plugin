#include "XRPLedgerRPCFunctions.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"


void UXRPLedgerRPCFunctions::ServerInfo(const FJsonResponseCallback& UserCallback)
{
  TArray<TSharedPtr<FJsonValue>> EmptyParamsArray;

  // FIX ME: Server URL won't be hardcoded in future, this is just for demo purposes
  SendJsonRpcRequest(TEXT("http://s1.ripple.com:51234/"), TEXT("server_info"), EmptyParamsArray, UserCallback);
}


void UXRPLedgerRPCFunctions::AccountInfo(const FString& AccountAddress, const FJsonResponseCallback& UserCallback)
{
  TSharedPtr<FJsonObject> ParamObject = MakeShareable(new FJsonObject());
  ParamObject->SetStringField("account", AccountAddress);

  TArray<TSharedPtr<FJsonValue>> ParamsArray;
  ParamsArray.Add(MakeShareable(new FJsonValueObject(ParamObject)));

  // FIX ME: Server URL won't be hardcoded in future, this is just for demo purposes
  SendJsonRpcRequest(TEXT("http://s1.ripple.com:51234/"), TEXT("account_info"), ParamsArray, UserCallback);
}

void UXRPLedgerRPCFunctions::TransactionInfo(const FString& TxHash, const FJsonResponseCallback& UserCallback)
{
  TSharedPtr<FJsonObject> ParamObject = MakeShareable(new FJsonObject());
  ParamObject->SetStringField("transaction", TxHash);

  TArray<TSharedPtr<FJsonValue>> ParamsArray;
  ParamsArray.Add(MakeShareable(new FJsonValueObject(ParamObject)));

  // FIX ME: Server URL won't be hardcoded in future, this is just for demo purposes
  SendJsonRpcRequest(TEXT("http://s1.ripple.com:51234/"), TEXT("tx"), ParamsArray, UserCallback);
}

void UXRPLedgerRPCFunctions::SendJsonRpcRequest(const FString& RequestUrl, const FString& MethodName, const TArray<TSharedPtr<FJsonValue>>& ParamsArray, const FJsonResponseCallback& UserCallback)
{
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
  HttpRequest->OnProcessRequestComplete().BindLambda([UserCallback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
      TSharedPtr<FJsonObject> JsonResponse = nullptr;
      if (bWasSuccessful && Response->GetResponseCode() == 200)
      {
        // Parse the JSON response
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
        FJsonSerializer::Deserialize(Reader, JsonResponse);
      }

      // Call the provided callback function with the parsed JSON data
      UserCallback(JsonResponse);
    });

  // Send the request
  HttpRequest->ProcessRequest();
}
