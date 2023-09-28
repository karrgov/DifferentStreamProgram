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
        std::cout << wordFilt.applyFilter(&stream) << std::endl;
        //sinkStream.printEverything();

        //test for SequenceReplaceFilter
        Stream secondStream("i weight hey no more weight key weight");
        SequenceReplaceFilter replaceFilter(&secondStream, "weight", "haha");
        char* result = replaceFilter.applyFilter(&secondStream);
        std::cout << result << std::endl;
        free(result);
        std::cout << "work" << std::endl;

        //test for PairFilter
        Stream thirdStream("i weight hey no more weight key weight");
        SequenceReplaceFilter replaceFilterSecond(&secondStream, "weight", "haha");
        WordFilter wordFilterSecond(&stream, "haha");
        PairFilter pairFilter(&stream, &replaceFilterSecond, &wordFilterSecond);
        char* resultSecond = pairFilter.applyFilter(&thirdStream);
        std::cout << resultSecond << std::endl;


        
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}