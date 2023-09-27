#pragma once
#include <iostream>
class Stream
{
    private:
    char* array = nullptr;
    int size;
    int capacity;

    public:
    Stream();
    Stream(int capacity);
    Stream(const char* str);
    Stream(const Stream& other);
    Stream& operator=(const Stream& other);
    ~Stream();

    void setData(const char* str);
    char* readInput();

    char* getArray();
    char* getArray() const;
    int sizeOfArray() const;
    int capacityOfArray();

    void incrementSize();
    void addElement(const char value);
    void expandArray();
    void printElements();
    char operator[] (int index) const;
};

class ConstStream : public Stream {
public:
	ConstStream(const char* str = "\0") : Stream(str) {}

	void setData(const char* str) = delete;
	void readInput() = delete;
};

class FileStream : public Stream
{
    public:
    FileStream(const char* filename);

};