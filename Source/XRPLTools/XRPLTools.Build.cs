// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XRPLTools : ModuleRules
{
	public XRPLTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[]
			{
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[]
			{
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);

		if (Target.Type == TargetType.Editor)
		{
			DynamicallyLoadedModuleNames.Add("Settings");
			PrivateIncludePathModuleNames.Add("Settings");
		}

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Http",
				"Json",
				"JsonUtilities",
				"Core",
				"CoreUObject",
				"Engine"
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
