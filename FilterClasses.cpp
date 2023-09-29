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
    WordFilter::WordFilter(Stream* stream, const char* word) : sourceStream(stream), filterWord(word), currentIndex(0)
    {

    }

    bool WordFilter::supposedToBeFreed()
    {
        return false;
    }

    SequenceReplaceFilter::SequenceReplaceFilter(Stream* stream, const char* target, const char* replacement)
        : sourceStream(stream), toBeReplaced(target), replaceWord(replacement), currentIndex(0)
    {

    }

    bool SequenceReplaceFilter::supposedToBeFreed()
    {
        return true;
    }
    
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
    : sourceStream(stream), firstFilter(first), secondFilter(second), currentIndex(0)
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

    char WordFilter::operator*() const
    {
        return *(sourceStream->getArray() + currentIndex);
    }

    void WordFilter::operator++()
    {
        if(currentIndex == sourceStream->sizeOfArray() - 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex++;
    }

    void WordFilter::operator--()
    {
        if(currentIndex < 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex--;
    }

    char WordFilter::operator[](int index) const 
    {
        int newIndex = currentIndex + index;
        assert(newIndex >= 0 && newIndex <= sourceStream->sizeOfArray() - 1);
        
        return *(sourceStream->getArray() + newIndex);
    }

    char* WordFilter::operator()(int start, int end) const
    {
        assert(start >= 0 && end <= sourceStream->sizeOfArray() - 1);
        int length = end - start + 1;
        char* result = new char[length + 1];
        int newIndex = currentIndex + start;
        for (int i = 0; i < length; i++) 
        {
            *(result + i) = *(sourceStream->getArray() + newIndex + i);
        }
        result[length] = '\0';
        return result; //memory should be deallocated after using the operator
    }
    /*
    PairFilter WordFilter::operator+(Filter& otherFilter) 
    {
        return PairFilter(this->sourceStream, this, &otherFilter);
    }
    */

    char SequenceReplaceFilter::operator*() const
    {
        return *(sourceStream->getArray() + currentIndex);
    }

    void SequenceReplaceFilter::operator++()
    {
        if(currentIndex == sourceStream->sizeOfArray() - 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex++;
    }

    void SequenceReplaceFilter::operator--()
    {
        if(currentIndex < 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex--;
    }

    char SequenceReplaceFilter::operator[](int index) const 
    {
        int newIndex = currentIndex + index;
        assert(newIndex >= 0 && newIndex <= sourceStream->sizeOfArray() - 1);
        
        return *(sourceStream->getArray() + newIndex);
    }

    char* SequenceReplaceFilter::operator()(int start, int end) const
    {
        assert(start >= 0 && end <= sourceStream->sizeOfArray() - 1);
        
        int length = end - start + 1;
        char* result = new char[length + 1];
        int newIndex = currentIndex + start;
        for (int i = 0; i < length; i++) 
        {
            *(result + i) = *(sourceStream->getArray() + newIndex + i);
        }
        result[length] = '\0';
        return result; //memory should be deallocated after using the operator
    }
    /*

    PairFilter SequenceReplaceFilter::operator+(Filter& otherFilter) 
    {
        return PairFilter(this->sourceStream, this, &otherFilter);
    }
    */

    char PairFilter::operator*() const
    {
        return *(sourceStream->getArray() + currentIndex);
    }

    void PairFilter::operator++()
    {
        if(currentIndex == sourceStream->sizeOfArray() - 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex++;
    }

    void PairFilter::operator--()
    {
        if(currentIndex < 1)
        {
            std::cerr << "There is not such element" << std::endl;
        }
        currentIndex--;
    }

    char PairFilter::operator[](int index) const 
    {
        int newIndex = currentIndex + index;
        assert(newIndex >= 0 && newIndex <= sourceStream->sizeOfArray() - 1);
    
        return *(sourceStream->getArray() + newIndex);
    }

    char* PairFilter::operator()(int start, int end) const
    {
        assert(start >= 0 && end <= sourceStream->sizeOfArray() - 1);
        int length = end - start + 1;
        char* result = new char[length + 1];
        int newIndex = currentIndex + start;
        for (int i = 0; i < length; i++) 
        {
            *(result + i) = *(sourceStream->getArray() + newIndex + i);
        }
        result[length] = '\0';
        return result; //memory should be deallocated after using the operator
    }
    /*
    PairFilter PairFilter::operator+(Filter& otherFilter) 
    {
        return PairFilter(this->sourceStream, this, &otherFilter);
    }
    */


