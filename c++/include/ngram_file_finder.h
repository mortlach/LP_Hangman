#ifndef NGRAM_FILE_FINDER_H
#define NGRAM_FILE_FINDER_H

#include <string>
#include <map>
#include <vector>

#include "file_io.h"

class ngram_file_finder : public file_io
{
    public:
        ngram_file_finder();
        virtual ~ngram_file_finder();

        bool get_files_ngram_letter(const std::string& ngram,const std::string& letters);

        bool get_files_ngram_letter(const std::string& ngram,
                        std::vector<std::string>& ngramFiles,const std::string& letters);


        bool get_files_ngram(const std::string& ngram);
        bool get_files_ngram(const std::string& ngram, std::vector<std::string>& ngramFiles);

        std::string setFileMapDataPath(const std::string& f){fileMapDataPath = f;}
        std::string getFileMapDataPath(){return fileMapDataPath;}

        std::string getFirstFile(){return ngramFiles[0];};


    protected:

    private:

        std::vector<std::string> ngramFiles;
        std::map<std::string, std::vector<std::string>> fileMap;
        bool stringMatch(const std::string& s1,const std::string& s2, int n1, int n2);
        bool entryExists(const std::string& key, std::vector<std::string>& values);
        bool get_map(const std::string& fn);

        std::string fileMapDataPath;
};
#endif // NGRAM_FILE_FINDER_H