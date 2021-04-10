// Copyright Epic Games, Inc. All Rights Reserved.



using UnrealBuildTool;



public class NetworkingTemplatePlugin : ModuleRules
{
	public NetworkingTemplatePlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;
		
		PublicIncludePaths.AddRange(
			new string[]
			{
			 //"NetworkingTemplatePlugin"                                         ,
			 //"NetworkingTemplatePlugin/Public"                                  ,
			 //"NetworkingTemplatePlugin/Public/Actors"                                  ,
			 //"NetworkingTemplatePlugin/Public/Actors/Pawns"                            ,
			 //"NetworkingTemplatePlugin/Public/Actors/Pawns/Characters"                 ,
			 //"NetworkingTemplatePlugin/Public/Framework"                               ,
			 //"NetworkingTemplatePlugin/Public/Networking"                              ,
			 //"NetworkingTemplatePlugin/Public/Networking/NetSlime"                     ,
			 //"NetworkingTemplatePlugin/Public/UserInterface"                           ,
			 //"NetworkingTemplatePlugin/Public/Utilities"                                 ,
			 //"NetworkingTemplatePlugin/Public/Utilities/Bitmask"                         ,
			// ... add public include paths required here ...
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] 
			{
				// ... add other private include paths required here ...
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core"              ,
				"CoreUObject"       ,
				"Engine"            ,
				"HeadMountedDisplay",
				"InputCore"         ,
				"Slate"             ,
				"SlateCore"         ,
				"UMG"               ,
				// ... add other public dependencies that you statically link with here ...

				// Added
                "AdvancedSessions"     ,
				"AdvancedSteamSessions",
				"NetSlime",
				"StaticUtils",

				// Networking
				"Networking"          ,
                "OnlineSubsystem"     ,
				"OnlineSubsystemNull" ,
                "OnlineSubsystemUtils",
                "Sockets"             ,
				"Steamworks"
			}
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
		);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}
