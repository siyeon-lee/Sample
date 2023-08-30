// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


DECLARE_LOG_CATEGORY_EXTERN(Mole, Log, All);

#define ML_LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define ML_LOG(Verbosity, Format, ...) UE_LOG(Mole, Verbosity, TEXT("%s %s"), *ML_LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
//(CategoryName, Verbosity, Format, ...)