// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DontLetMeGo : ModuleRules
{
	public DontLetMeGo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG" });
	}
}
