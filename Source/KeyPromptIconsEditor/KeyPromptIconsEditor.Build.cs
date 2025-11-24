// Copyright 2023 Iraj Mohtasham aurelion.net 

using UnrealBuildTool;

public class KeyPromptIconsEditor : ModuleRules
{
	public KeyPromptIconsEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore","ApplicationCore","RenderCore",
			"RHI","Projects","BlueprintGraph","GraphEditor","KismetCompiler" });

			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"KeyPromptIcons"
				,"UnrealEd"

				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		/*PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore",
				"RenderCore",
				"RHI",
			}
		);*/
		
		PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"ImageWrapper",
				"TargetPlatform",
			}
		);
		if (Target.Type != TargetType.Server)
		{
			PrivateIncludePathModuleNames.AddRange(
				new string[] {
					"SlateRHIRenderer",
				}
			);

			DynamicallyLoadedModuleNames.AddRange(
				new string[] {
					"ImageWrapper",
					"SlateRHIRenderer",
				}
			);
		}
	}
}
