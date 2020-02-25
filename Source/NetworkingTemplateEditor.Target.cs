// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class NetworkingTemplateEditorTarget : TargetRules
{
	public NetworkingTemplateEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;


		bUsesSteam = true;   // Uses Steamworks. (Valve) 
 
		bIWYU        = true;   // Enables "include what you use" by default for modules in this target. Changes the default PCH mode for any module in this project to PCHUsageModule.UseExplicitOrSharedPCHs.
		bEnforceIWYU = true;   // Enforce "include what you use" rules; warns if monolithic headers (Engine.h, UnrealEd.h, etc...) are used, and checks that source files include their matching header first.

		bUseAdaptiveUnityBuild = false;   // Use a heuristic to determine which files are currently being iterated on and exclude them from unity blobs, result in faster incremental compile times. The current implementation uses the read-only flag to distinguish the working set, assuming that files will be made writable by the source control system if they are being modified. This is true for Perforce, but not for Git 


		ExtraModuleNames.AddRange( new string[] { "NetworkingTemplate" } );
	}
}
