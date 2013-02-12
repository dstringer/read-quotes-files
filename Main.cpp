#include <iostream>
#include <dirent.h>
#include <ctime>

#include "ReadGZippedTAQQuotesFile.h"

int main ()
{
    DIR* dir;
    dirent* pdir;

    char file[100];
    const char * directory = "/Users/davidstringer/Data/SQL-Data/20070620/";
    
    long _totalBytes = 0;
    int _nfiles = 0;
    
    dir = opendir(directory);
    
    // Count the number of files
    while ((pdir = readdir(dir))) {
        ++_nfiles;
    }
    std::cout << "Found " << _nfiles << " files." << std::endl;
    
    ReadGZippedTAQQuotesFile * r = new ReadGZippedTAQQuotesFile[_nfiles];
        
    dir = opendir(directory);
    // Loop over all files in the directory
    for (int i = 0; i < _nfiles; ++i) 
    {
        pdir = readdir(dir);
        if (pdir->d_name[0] == '.')
            continue;
        strcpy(file, directory);
        strcat(file, pdir->d_name);
        r[i] = ReadGZippedTAQQuotesFile(file);
        _totalBytes += r[i].getNBytes();
        std::memset(file, '0', sizeof(file));
    }
    closedir(dir);
    
    // Get the runtime
    std::cout << "Loaded " << _totalBytes << " bytes." << std::endl;
    float seconds = (static_cast<float>(std::clock()))/CLOCKS_PER_SEC;
    std::cout << "Runtime: " << seconds << " seconds." << std::endl;
}

