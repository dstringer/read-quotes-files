#ifndef READGZIPPEDTAQQUOTESFILE_H
#define READGZIPPEDTAQQUOTESFILE_H

#include <iostream>

class ReadGZippedTAQQuotesFile
{
    public:
        ReadGZippedTAQQuotesFile() {};
        ReadGZippedTAQQuotesFile(const char* filename);
        void displayRecords(int firstIndex, int lastIndex);
        
        int getNBytes() { return _nBytes; };
        
    private:
        const char* _filename;
        char _header[8];
        int _nBytes;
        int _secsFromEpoch;
        int _nRecs;
        
        int*    _millisecondsFromMidnight;
        int*    _bidSize;
        float*  _bidPrice;
        int*    _askSize;
        float*  _askPrice;

        void readByteBackwards(std::istream &inf, char* mem);
};

#endif // READGZIPPEDTAQQUOTESFILE_H
