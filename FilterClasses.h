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