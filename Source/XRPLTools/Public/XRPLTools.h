// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"


/**
 * Module for the XRPLTools plugin.
 * This handles the startup and shutdown lifecycle of the plugin
 * as well as the plugin settings.
 */
class FXRPLToolsModule : public IModuleInterface
{
public:

  /** IModuleInterface implementation */

  /** Called when the module is started up during engine initialization. */
  virtual void StartupModule() override;
  /** Called when the module is shut down during engine exit. */
  virtual void ShutdownModule() override;

private:

  /** Handles the event when settings are saved. Returns true if settings are saved successfully. */
  bool HandleSettingsSaved();

  /** Registers the plugin settings with the engine. */
  void RegisterSettings();
  /** Unregisters the plugin settings from the engine. */
  void UnregisterSettings();

private:

  /** Tracks the previous state of the WebSocket usage flag. */
  bool bPrevUseWebsockets = false;
};
