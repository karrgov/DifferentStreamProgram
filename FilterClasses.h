#pragma once
#include "StreamClasses.h"
class Filter
{
    public:
    virtual char* applyFilter(Stream* stream) = 0;
    virtual bool supposedToBeFreed() = 0;
};

class WordFilter : public Filter
{
private:
    Stream* sourceStream;
    const char* filterWord;

public:
    WordFilter(Stream* stream, const char* word);

    //void removeEveryWordMatch();
    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override;
};

class SequenceReplaceFilter : public Filter
{
private:
    Stream* sourceStream;
    const char* toBeReplaced;
    const char* replaceWord;

public:
    SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement);

    //char* replaceTargetWithReplacement();
    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override; //true because this applyFilter returns pointer to heap allocated memory
};


class PairFilter : public Filter
{
    private:
    Stream* sourceStream;
    Filter* firstFilter;
    Filter* secondFilter;

    public:
    PairFilter(Stream* stream, Filter* first, Filter* second);
    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override;

};

