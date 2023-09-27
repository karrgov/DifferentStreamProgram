#define _CRT_SECURE_NO_WARNINGS
#include "StreamClasses.h"
#include "FilterClasses.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>

    WordFilter::WordFilter(Stream* stream, const char* word) : sourceStream(stream), filterWord(word) 
    {

    }

    void WordFilter::removeEveryWordMatch()
    {
       int i = 0;
       int streamLength = sourceStream->sizeOfArray();
       int wordLength = strlen(filterWord);
       while(i < streamLength)
       {
            if(strstr((sourceStream->getArray() + i), filterWord) == (sourceStream->getArray() + i))
            {
                streamLength -= wordLength;
                for(int j = i; j < streamLength; j++)
                {
                    *(sourceStream->getArray() + j) = *(sourceStream->getArray() + j + wordLength);
                }
            }
            else
            {
                i++;
            }
       }
       *(sourceStream->getArray() + i) = '\0';
    }