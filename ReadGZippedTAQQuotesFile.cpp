#include "ReadGZippedTAQQuotesFile.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include "gzstream.h"

ReadGZippedTAQQuotesFile::ReadGZippedTAQQuotesFile(const char* filename)
    : _filename(filename)
{
    // Prepare the stream
    igzstream file;
    file.open(filename, std::ios::in | std::ios::binary);
    // Read the _header data
    readByteBackwards(file, reinterpret_cast<char*>(&_secsFromEpoch));
    readByteBackwards(file, reinterpret_cast<char*>(&_nRecs));
    //std::cout << "Seconds from epoch: " << _secsFromEpoch << std::endl;
    //std::cout << "Number of records: " << _nRecs << std::endl;

    // Allocate memory for acatual data
    _nBytes = _nRecs*4*5;
    //_nBytes = 10278680;
    //_nRecs = 513934;
    
    //std::cout << "Allocating " << _nBytes << " bytes of memory" << std::endl;
    _millisecondsFromMidnight = new int[_nBytes];
    _bidSize = new int[_nBytes];
    _bidPrice = new float[_nBytes];
    _askSize = new int[_nBytes];
    _askPrice = new float[_nBytes];
    
    // Read the data into memory
    for (int j = 0; j < _nRecs; ++j)
        readByteBackwards(file, reinterpret_cast<char*>(_millisecondsFromMidnight + j));
    for (int j = 0; j < _nRecs; ++j)
        readByteBackwards(file, reinterpret_cast<char*>(_bidSize + j));
    for (int j = 0; j < _nRecs; ++j)
        readByteBackwards(file, reinterpret_cast<char*>(_bidPrice + j));
    for (int j = 0; j < _nRecs; ++j)
        readByteBackwards(file, reinterpret_cast<char*>(_askSize + j));
    for (int j = 0; j < _nRecs; ++j)
        readByteBackwards(file, reinterpret_cast<char*>(_askPrice + j));
    
    file.close();
    
    //displayRecords(0,10);
}

// Read 4 bytes from the input stream and store them in reverse order in memory
// to correct for big endianess in the input data
void ReadGZippedTAQQuotesFile::readByteBackwards(std::istream &inf, char* mem)
{
    inf.read(mem,4);
    unsigned int * n = reinterpret_cast<unsigned int*>(mem);
    *n = (*n >> 24) |
         ((*n << 8) & 0x00FF0000 ) |
         ((*n >> 8) & 0x0000FF00 ) |
         (*n << 24);

    /*
    char c[2];
    std::memcpy(c, mem, 1);
    std::memcpy(c+1, mem+1, 1);
    std::memcpy(mem, mem+3, 1);
    std::memcpy(mem+1, mem+2, 1);
    std::memcpy(mem+2, c+1, 1);
    std::memcpy(mem+3, c, 1);
    */
    /*
    std::swap(*mem, *(mem+3));
    std::swap(*(mem+1),*(mem+2));
    */
}

void ReadGZippedTAQQuotesFile::displayRecords(int firstIndex, int lastIndex)
{
    for (int i = firstIndex; i < lastIndex; ++i)
    {
        std::cout << std::setw(4) << i << 
            std::setw(10) << *(_millisecondsFromMidnight + i) << 
            std::setw(5) << *(_bidSize + i) << 
            std::setprecision(2) << std::fixed << std::setw(8) <<
            *(_bidPrice + i) << 
            std::setw(5) << *(_askSize + i) <<
            std::setprecision(2) << std::fixed << std::setw(8) <<
            *(_askPrice + i) <<
            std::endl;
    }
}
