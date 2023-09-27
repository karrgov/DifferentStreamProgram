#pragma once
#include "StreamClasses.h"
class Sink 
{
    private:
    Stream *streamPointer;

    public:
    Sink(Stream* stream);

    Stream* getStreamPointer();
    void printEverything();
};

class FileSink : public Sink
{
private:
    const char* filename;

public:
    FileSink(Stream* stream, const char* filename);

    void saveTextDataToFile();
};