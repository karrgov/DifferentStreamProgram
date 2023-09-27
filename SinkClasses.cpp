#define _CRT_SECURE_NO_WARNINGS
#include "SinkClasses.h"
#include <cstring>
#include <fstream>

Sink::Sink(Stream* stream) : streamPointer(stream) {}

Stream* Sink::getStreamPointer()
{
    return streamPointer;
}

void Sink::printEverything() 
{
    if (streamPointer != nullptr) 
    {
        std::cout << streamPointer->getArray() << std::endl;
    } 
    else 
    {
        std::cerr << "Trying to print nullptr!" << std::endl;
    }
}

FileSink::FileSink(Stream* stream, const char* filename) : Sink(stream), filename(filename) 
{

}

void FileSink::saveTextDataToFile()
{
    std::ofstream outputFile(filename);

    if (!outputFile)
    {
        std::cerr << "Could not open the file you've chose: " << filename << std::endl;
        return;
    }

    if (this->getStreamPointer() != nullptr)
    {
        const char* content = this->getStreamPointer()->getArray();
        outputFile << content;
    }
    else
    {
        std::cerr << "Nullptr!" << std::endl;
    }

    outputFile.close();
}