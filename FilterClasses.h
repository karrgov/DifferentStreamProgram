#pragma once
#include "StreamClasses.h"
class Filter
{
    public:
    virtual char* applyFilter(Stream* stream) = 0;
    virtual bool supposedToBeFreed() = 0;

    virtual char operator*() const = 0;
    virtual void operator++() = 0;
    virtual void operator--() = 0;
    virtual char operator[](int index) const = 0;
    virtual char* operator()(int start, int end) const = 0;
};

class WordFilter : public Filter
{
private:
    Stream* sourceStream;
    const char* filterWord;
    int currentIndex;

public:
    WordFilter(Stream* stream, const char* word);

    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override;

    virtual char operator*() const override;
    virtual void operator++() override;
    virtual void operator--() override;
    virtual char operator[](int index) const override;
    virtual char* operator()(int start, int end) const override;
    //PairFilter operator+(Filter& otherFilter);
};

class SequenceReplaceFilter : public Filter
{
private:
    Stream* sourceStream;
    const char* toBeReplaced;
    const char* replaceWord;
    int currentIndex;

public:
    SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement);

    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override; //true because this applyFilter returns pointer to heap allocated memory

    virtual char operator*() const override;
    virtual void operator++() override;
    virtual void operator--() override;
    virtual char operator[](int index) const override;
    virtual char* operator()(int start, int end) const override;
    //PairFilter operator+(Filter& otherFilter);
};


class PairFilter : public Filter
{
    private:
    Stream* sourceStream;
    Filter* firstFilter;
    Filter* secondFilter;
    int currentIndex;

    public:
    PairFilter(Stream* stream, Filter* first, Filter* second);

    virtual char* applyFilter(Stream* stream) override;
    virtual bool supposedToBeFreed() override;

    virtual char operator*() const override;
    virtual void operator++() override;
    virtual void operator--() override;
    virtual char operator[](int index) const override;
    virtual char* operator()(int start, int end) const override;
    //PairFilter operator+(Filter& otherFilter);

};

