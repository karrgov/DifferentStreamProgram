#define _CRT_SECURE_NO_WARNINGS
#include "StreamClasses.h"
#include "FilterClasses.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>
#include <stdlib.h>
#include <string.h>
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

    SequenceReplaceFilter::SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement)
        : sourceStream(stream), toBeReplaced(target), replaceWord(replacement) 
    {

    }

    char* SequenceReplaceFilter::replaceTargetWithReplacement()
    {
        int toBeReplacedLength = strlen(toBeReplaced); 
        int replaceWordLength = strlen(replaceWord);
        int oldStreamLength = sourceStream->sizeOfArray();

        char* afterStream;
        if(toBeReplacedLength == replaceWordLength)
        {
            afterStream = (char*) malloc((oldStreamLength + 1) * sizeof(char));
        }
        else
        {
            int occurrencesOfToBeReplaced = 0;

            int i = 0;
            while(i < oldStreamLength)
            {
                if((strstr((sourceStream->getArray() + i), toBeReplaced)) == (sourceStream->getArray() + i))
                {
                    occurrencesOfToBeReplaced++;
                    i += oldStreamLength;
                }
                else
                {
                    i++;
                }
            }
            int diffInLength = replaceWordLength - toBeReplacedLength;
            int newStreamLength = oldStreamLength;
            newStreamLength += occurrencesOfToBeReplaced * diffInLength; //if diffInLength is positive then newStreamLength will be more than oldStreamLength
            //if diffInLength is negative then newStreamLength will be less than oldStreamLength
            afterStream = (char*) malloc((newStreamLength + 1) * sizeof(char));
        }
        //now we have already allocated the needed memory and we should actually replace the words

        int i = 0;
        int j = 0;

        while(i < oldStreamLength)
        {
            if((strstr((sourceStream->getArray() + i), toBeReplaced)) == (sourceStream->getArray() + i))
            {
                strcpy((afterStream + j), replaceWord);
                i += toBeReplacedLength;
                j += replaceWordLength;
            }
            else 
            {
                *(afterStream + j) = *(sourceStream->getArray() + i);
                i++;
                j++;
            }
        }
        *(afterStream + j) = '\0';
        return afterStream;
    }