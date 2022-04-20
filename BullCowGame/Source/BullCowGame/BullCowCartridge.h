// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "Kismet/KismetMathLibrary.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString &Input) override;

	// Your declarations go below!
private:
	void InitGame();
	bool isGuessGood(const FString &Input);

	TArray<FString> words;
	FString hiddenWord;
	int32 bulls;
	int32 cows;
	int32 lives;

	bool bGameOver;

	static bool IsIsogram(const FString &Word);

	void CheckCharacters(const FString &Input);

	bool ContainsCharacter(const FString &SearchString, const char &LookChar) const;

	void GameOver();
};
