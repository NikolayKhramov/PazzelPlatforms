// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class PazzelPlatform_OrEditorTarget : TargetRules
{
	public PazzelPlatform_OrEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "PazzelPlatform_Or" } );
	}
}
