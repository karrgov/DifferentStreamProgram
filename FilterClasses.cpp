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

    bool WordFilter::supposedToBeFreed()
    {
        return false;
    }
    /*

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
    */

    SequenceReplaceFilter::SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement)
        : sourceStream(stream), toBeReplaced(target), replaceWord(replacement) 
    {

    }

    bool SequenceReplaceFilter::supposedToBeFreed()
    {
        return true;
    }
    /*

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
    */
    char* WordFilter::applyFilter(Stream* stream)
    {
       int i = 0;
       int streamLength = stream->sizeOfArray();
       int wordLength = strlen(filterWord);
       while(i < streamLength)
       {
            if(strstr((stream->getArray() + i), filterWord) == (stream->getArray() + i))
            {
                streamLength -= wordLength;
                for(int j = i; j < streamLength; j++)
                {
                    *(stream->getArray() + j) = *(stream->getArray() + j + wordLength);
                }
            }
            else
            {
                i++;
            }
       }
       *(stream->getArray() + i) = '\0';
       return stream->getArray();
    }


    char* SequenceReplaceFilter::applyFilter(Stream* stream) 
    {
        int toBeReplacedLength = strlen(toBeReplaced); 
        int replaceWordLength = strlen(replaceWord);
        int oldStreamLength = stream->sizeOfArray();

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
                if((strstr((stream->getArray() + i), toBeReplaced)) == (stream->getArray() + i))
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
            if((strstr((stream->getArray() + i), toBeReplaced)) == (stream->getArray() + i))
            {
                strcpy((afterStream + j), replaceWord);
                i += toBeReplacedLength;
                j += replaceWordLength;
            }
            else 
            {
                *(afterStream + j) = *(stream->getArray() + i);
                i++;
                j++;
            }
        }
        *(afterStream + j) = '\0';
        return afterStream;
    }

    PairFilter::PairFilter(Stream* stream, Filter* first, Filter* second)
    : sourceStream(stream), firstFilter(first), secondFilter(second)
    {
    }

    bool PairFilter::supposedToBeFreed()
    {
        return false;
    }

    char* PairFilter::applyFilter(Stream* stream) 
    {

        char* firstResult = firstFilter->applyFilter(stream);
        Stream resultStream(firstResult);
        if(firstFilter->supposedToBeFreed())
        {
            free(firstResult);
        }

        char* secondResult = secondFilter->applyFilter(&resultStream);
        (*stream) = resultStream;
        if(secondFilter->supposedToBeFreed())
        {
            free(secondResult);
        }

        return stream->getArray();
    }