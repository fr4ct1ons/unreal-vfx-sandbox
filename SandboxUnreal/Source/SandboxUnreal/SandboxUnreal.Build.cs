// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SandboxUnreal : ModuleRules
{
	public SandboxUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
