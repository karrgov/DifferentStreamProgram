#pragma once
#include "StreamClasses.h"
class WordFilter
{
private:
    const char* filterWord;
    Stream* sourceStream;

public:
    WordFilter(Stream* stream, const char* word);

    void removeEveryWordMatch();
};

class SequenceReplaceFilter
{
private:
    const char* toBeReplaced;
    const char* replaceWord;
    Stream* sourceStream;

public:
    SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement);

    char* replaceTargetWithReplacement();
};