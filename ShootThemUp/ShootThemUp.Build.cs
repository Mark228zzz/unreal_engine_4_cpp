// Stoot Them Up Game, All Rights Reserved.

using UnrealBuildTool;

public class ShootThemUp : ModuleRules
{
	public ShootThemUp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"Niagara",
			"GameplayTasks",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[] {
			"ShootThemUp/Public/Player",
			"ShootThemUp/Public/Components",
			"ShootThemUp/public/Dev",
            "ShootThemUp/public/Weapon",
            "ShootThemUp/public/UI",
			"ShootThemUp/public/Animations",
			"StootThemUp/public/Weapon/Components",
			"StootThemUp/public/AI",
			"StootThemUp/public/AI/Tasks",
			"StootThemUp/public/AI/Services",
			"StootThemUp/public/AI/EQS",
			"StootThemUp/public/AI/Decorators"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
