#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <cstring>
#include <cassert>
#include "StreamClasses.h"
#include "SinkClasses.h"

int main()
{
    try
    {
        //test for Stream class
        //Stream stream;
        //std::cout << "Input text data and terminate by Control + D:\n";
        //char* input = stream.readInput();
        Stream stream("anfgsdgdsg");
        
        //test for Sink class
        Sink sinkStream(&stream);
        sinkStream.printEverything();

        //test for ConstStream class
        ConstStream constantStream("helloworld123");

        //test for FileStream class
        FileStream streamFromFile("WriteFromFile.txt");

        //test for FileSink class
        FileSink streamToFile(&stream, "Text.txt");
        streamToFile.saveTextDataToFile();
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}