// Copyright Epic Games, Inc. All Rights Reserved.

#include "XRPLTools.h"

#include "Core.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "XRPLedgerRPCFunctions.h"
#include "XRPLToolsSettings.h"


#define LOCTEXT_NAMESPACE "FXRPLToolsModule"


/**
 * @brief Starts up the XRPLTools module during engine initialization.
 *
 * This method handles any setup required when the XRPLTools module is
 * initialized by the engine.
 */
void FXRPLToolsModule::StartupModule()
{
	RegisterSettings();
}

/**
 * @brief Shuts down the XRPLTools module during engine exit.
 *
 * This method performs cleanup operations required when the XRPLTools module
 * is unloaded by the engine.
 */
void FXRPLToolsModule::ShutdownModule()
{
  if (UObjectInitialized())
  {
    UnregisterSettings();
  }
}

/**
 * @brief Handles the event triggered when the module settings are saved.
 *
 * This method provides additional logic for when the XRPLTools module
 * settings are saved, e.g. it can be used to apply or reload certain settings.
 *
 * @return true If the settings are handled successfully, false otherwise.
 */
bool FXRPLToolsModule::HandleSettingsSaved()
{
  UXRPLToolsSettings* Settings = GetMutableDefault<UXRPLToolsSettings>();
  if (Settings)
  {
    if (bPrevUseWebsockets != Settings->bUseWebsockets)
    {
      UXRPLedgerRPCFunctions::SetUseWebsockets(Settings->bUseWebsockets);
    }
    bPrevUseWebsockets = Settings->bUseWebsockets;
    Settings->SaveConfig();
    return true;
  }

  return false;
}

/**
 * @brief Registers the XRPLTools module settings with the engine.
 *
 * This method handles the registration of the XRPLTools module settings,
 * making them available for the user to configure in the engine's settings UI.
 */
void FXRPLToolsModule::RegisterSettings()
{
  if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
  {
    UXRPLToolsSettings* Settings = GetMutableDefault<UXRPLToolsSettings>();
    if (Settings)
    {
      // Update the static variable based on the configuration value
      UXRPLedgerRPCFunctions::SetUseWebsockets(Settings->bUseWebsockets);
      bPrevUseWebsockets = Settings->bUseWebsockets;

      ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "XRPLTools", "Default",
        LOCTEXT("RuntimeSettingsName", "XRPL Tools"),
        LOCTEXT("RuntimeSettingsDescription", "Configure the XRPL Tools Plugin."),
        Settings
      );

      if (SettingsSection.IsValid())
      {
        SettingsSection->OnModified().BindRaw(this, &FXRPLToolsModule::HandleSettingsSaved);
      }
    }
  }
}

/**
 * @brief Unregisters the XRPLTools module settings from the engine.
 *
 * This method removes the XRPLTools module settings from the engine's
 * settings UI, effectively disabling them from being configured by the user.
 */
void FXRPLToolsModule::UnregisterSettings()
{
  if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
  {
    SettingsModule->UnregisterSettings("Project", "XRPLTools", "Default");
  }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXRPLToolsModule, XRPLTools)
