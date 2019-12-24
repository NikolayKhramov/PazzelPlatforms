// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class PazzelPlatform_OrTarget : TargetRules
{
	public PazzelPlatform_OrTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "PazzelPlatform_Or" } );
	}
}
