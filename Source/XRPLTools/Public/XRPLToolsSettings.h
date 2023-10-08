#pragma once

#include "CoreMinimal.h"

#include "XRPLToolsSettings.generated.h"

// -----------------------------------------------------------------------
// EXAMPLES
// Read:
// const UXRPLToolsSettings* Settings = GetDefault<UXRPLToolsSettings>();
// if (Settings->bUseWebsockets)
// {
//   // Do something
// }
// -----------------------------------------------------------------------
// Write:
// UXRPLToolsSettings* Settings = GetMutableDefault<UXRPLToolsSettings>();
// Settings->bUseWebsockets = false;
// Settings->SaveConfig();
// -----------------------------------------------------------------------


/**
 * @brief XRPLTools Plugin settings object.
 *
 * This class holds the configurable settings for the XRPLTools Plugin.
 * These settings can be changed by users via the Unreal Editor under Project Settings.
 */
UCLASS(config=XRPLTools)
class XRPLTOOLS_API UXRPLToolsSettings : public UObject
{
  GENERATED_BODY()

public:

  /** Determines whether to use WebSockets for calling public API methods. */
  UPROPERTY(Config, EditAnywhere, Category = "XRPLedger")
  bool bUseWebsockets = false;
};
