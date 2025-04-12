// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EnterThePotato : ModuleRules
{
	public EnterThePotato(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject",
			"Engine", 
			"InputCore", 
			"NavigationSystem", 
			"AIModule", 
			"Niagara", 
			"EnhancedInput",
			"GameplayTasks",
			"UMG",
			"Slate",
			"SlateCore",
            "Json",
            "JsonUtilities"
		});
    }
}
