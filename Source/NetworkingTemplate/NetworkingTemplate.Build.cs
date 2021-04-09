// Fill out your copyright notice in the Description page of Project Settings.



using UnrealBuildTool;



public class NetworkingTemplate : ModuleRules
{
	public NetworkingTemplate(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;



		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });



        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDependencyModuleNames.AddRange
            (
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
                    
                    // Added
                    "AdvancedSessions"     ,
                    "AdvancedSteamSessions",
				  //"VRExpansionPlugin"    ,
                  //"OpenVRExpansionPlugin",
                  
                  // Networking
					"Networking"          ,
                    "OnlineSubsystem"     ,
					"OnlineSubsystemNull" ,
                    "OnlineSubsystemUtils",
                    "Sockets"             ,
					"Steamworks"
                }
            );
        }

		PublicIncludePaths.AddRange
		(   
			new string[]
			{
			 "NetworkingTemplate",
			// ... add public include paths required here ...
			}
		);

		/* VR Required Modules */
		//if (Target.Platform == UnrealTargetPlatform.Win64)
		//{
		//    PrivateDependencyModuleNames.AddRange(new string[] { "SteamVR", "SteamVRController" });
		//}
		//else
		//{
		//    PrivateDependencyModuleNames.AddRange(new string[] { });
		//}
	}



	// Uncomment if you are using Slate UI
	//PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
	
	// Uncomment if you are using online features.
	//PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem" });

	// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
}

