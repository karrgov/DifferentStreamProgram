#define _CRT_SECURE_NO_WARNINGS
#include "StreamClasses.h"
#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <exception>

Stream::Stream(int capacity)
{
    this->capacity = capacity;
    this->array = new char[capacity];
    this->size = 0;
}

Stream::Stream()
{
    this->capacity = 10;
    this->array = new char[capacity];
    this->size = 0;
    *(this->array + size++) = '\0';
}

Stream::Stream(const char* str) : Stream() 
{
    setData(str);
}

Stream::Stream(const Stream& other)
{
    this->capacity = other.capacity;
    array = new char[capacity];
    this->size = other.size;
    for(int i = 0; i < size; ++i) 
    {
        *(array + i) = other.array[i];
    }
}

Stream::~Stream()
{
    delete[] array;
}

void Stream::setData(const char* str) 
{
    if (str == nullptr) 
    {
        str = "";
    }

    int strLength = strlen(str) + 1;
    while (strLength > capacity) 
    {
        expandArray();
    }

    strcpy(array, str);
    size = strLength;
}

char* Stream::readInput()
{
    char ch;
    while (std::cin.get(ch)) 
    {
        if (size == capacity) 
        {
            expandArray();
        }
        array[size++] = ch;
    }

    if (capacity <= size)
    {
        expandArray();
    }

    array[size] = '\0';
    return array;
}

char* Stream::getArray()
{
    return array;
}

char* Stream::getArray() const
{
    return array;
}

int Stream::sizeOfArray() const
{
    return this->size;
}

void Stream::incrementSize()
{
    size++;
}

int Stream::capacityOfArray()
{
    return this->capacity;
}

void Stream::addElement(const char value)
{
    if(size == capacity)
    {
        expandArray();
    }
    *(array + size) = value;
    size++;
}

void Stream::expandArray()
{
    char* tempArray = new char[capacity * 2];
    capacity = capacity * 2;
    for (int i = 0; i < size; i++)
    {
        *(tempArray + i) = *(array + i);
    }
    delete[] array;
    array = tempArray;
}

char Stream::operator[] (int index) const
{
    assert(index >= 0 && index < size);
    return *(array + index);
}

Stream& Stream::operator=(const Stream& other) 
{
    if (this != &other) 
    {
        setData(other.array);
    }
    return *this;
}


FileStream::FileStream(const char* filename) : Stream(0)
    {
        std::ifstream file(filename);

        if (!file)
        {
            std::cerr << "Could not open the file you've chose: " << filename << std::endl;
            return;
        }
        char ch;
        while (file.get(ch))
        {
           this->addElement(ch);
        }
        file.close();
    }
