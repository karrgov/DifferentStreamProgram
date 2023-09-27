#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <cstring>
#include <cassert>
#include "StreamClasses.h"
#include "SinkClasses.h"
#include "FilterClasses.h"

int main()
{
    try
    {
        //test for Stream class
        //Stream stream;
        //std::cout << "Input text data and terminate by Control + D:\n";
        //char* input = stream.readInput();
        Stream stream("ag kar jf kar");
        
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

        //test for WordFilter class
        WordFilter wordFilt(&stream, "kar");
        wordFilt.removeEveryWordMatch();
        sinkStream.printEverything();

        
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}