// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class XXII : ModuleRules
{
	public XXII(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"XXII",
			"XXII/Variant_Platforming",
			"XXII/Variant_Platforming/Animation",
			"XXII/Variant_Combat",
			"XXII/Variant_Combat/AI",
			"XXII/Variant_Combat/Animation",
			"XXII/Variant_Combat/Gameplay",
			"XXII/Variant_Combat/Interfaces",
			"XXII/Variant_Combat/UI",
			"XXII/Variant_SideScrolling",
			"XXII/Variant_SideScrolling/AI",
			"XXII/Variant_SideScrolling/Gameplay",
			"XXII/Variant_SideScrolling/Interfaces",
			"XXII/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
