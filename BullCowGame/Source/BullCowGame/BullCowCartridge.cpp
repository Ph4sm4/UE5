// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
//#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(words, *WordListPath, UBullCowCartridge::IsIsogram); // initializing our array with the words from a txt file

    InitGame();
}

void UBullCowCartridge::InitGame()
{
    int32 rand = FMath::RandRange(0, words.Num() - 1);
    hiddenWord = words[rand];

    lives = hiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cow Game"));
    PrintLine(TEXT("Hidden word: %s"), *hiddenWord);
    PrintLine(TEXT("You've got %i lives!"), lives);
    PrintLine(FString::Printf(TEXT("Guess the %i letter word!"), hiddenWord.Len()));
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        InitGame();
        return;
    }
    bulls = 0;
    cows = 0;
    if (Input.Len() != hiddenWord.Len())
    {
        PrintLine(TEXT("The number of letters in the word must be the same!"));
        return;
    }
    if (!IsIsogram(Input))
    {
        PrintLine(TEXT("You need to enter an isogram!"));
        return;
    }

    CheckCharacters(Input);

    if (!lives)
    {
        PrintLine(TEXT("You ran out of lives! GG"));
        PrintLine(FString::Printf(TEXT("The word was: %s"), *hiddenWord));
        GameOver();
    }
    else if (bulls == hiddenWord.Len())
    {
        PrintLine(TEXT("You won! Good job"));
        GameOver();
    }
    else
    {
        PrintLine(TEXT("Wrong word. You got %i bulls and %i cows"), bulls, cows);
        PrintLine(TEXT("Remaining lifes: %i"), lives);
    }
}

void UBullCowCartridge::GameOver()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again"));
}

void UBullCowCartridge::CheckCharacters(const FString &Input)
{
    if (Input == hiddenWord)
    {
        bGameOver = true;
        bulls = hiddenWord.Len();
        return;
    }
    bool isSomethingWrong = false;

    for (int i = 0; i < hiddenWord.Len(); i++)
    {
        if (Input[i] == hiddenWord[i])
        {
            bulls++;
        }
        else
        {
            if (ContainsCharacter(hiddenWord, Input[i]))
            {
                cows++;
            }
            isSomethingWrong = true;
        }
    }

    if (isSomethingWrong)
    {
        lives--;
    }
}

bool UBullCowCartridge::ContainsCharacter(const FString &SearchString, const char &LookChar) const
{
    for (auto letter : SearchString)
    {
        if (letter == LookChar)
        {
            return true;
        }
    }
    return false;
}

bool UBullCowCartridge::IsIsogram(const FString &Word)
{
    for (int32 i = 0; i < Word.Len() - 1; i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word[i] == Word[j])
                return false;
        }
    }

    return true;
}