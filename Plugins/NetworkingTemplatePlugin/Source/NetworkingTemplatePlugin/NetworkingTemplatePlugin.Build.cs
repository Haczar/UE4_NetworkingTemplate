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
			 "NetworkingTemplatePlugin"                                         ,
			 "NetworkingTemplatePlugin/Actors"                                  ,
			 "NetworkingTemplatePlugin/Actors/Pawns"                            ,
			 "NetworkingTemplatePlugin/Actors/Pawns/Characters"                 ,
			 "NetworkingTemplatePlugin/Framework"                               ,
			 "NetworkingTemplatePlugin/Networking"                              ,
			 "NetworkingTemplatePlugin/Networking/NetSlime"                     ,
			 "NetworkingTemplatePlugin/UserInterface"                           ,
			 "NetworkingTemplatePlugin/Utilities"                                 ,
			 "NetworkingTemplatePlugin/Utilities/Bitmask"                         ,
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
