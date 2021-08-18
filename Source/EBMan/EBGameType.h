// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
enum  class ERoundState :uint8
{
	InMenu,
	Preparing,
	Running,
	Win,
	Fail,

	Unknown
};

UENUM(BlueprintType)
enum  class EGameRound :uint8
{
	InMenu = 0,
	First,
	FirstNight,
	Second,
	SecondNight,
	Third,
	ThirdNight,
	Fourth,
	FourthNight,
	Fifth,
	FifthNight,

	Endless,
	TwoPlayer,

	Max,
};