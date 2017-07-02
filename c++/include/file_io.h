#ifndef FILE_IO_H
#define FILE_IO_H

#include <vector>
#include <string>
#include "structs.h"

class file_io
{
    public:
        file_io();
        virtual ~file_io();

        bool read_ngram_data_file(const std::string& fn);
        bool read_ngram_data_file(const std::string& fn, std::vector<std::vector<std::string>>& fileData);
        std::vector<std::vector<std::string>>& getFileData(){return fileData;}

        void split_by_blank(std::string& line, std::vector<std::string>& tokens);
        void split_by_blank(std::istringstream& iss, std::vector<std::string>& tokens);

    protected:
        std::vector<std::vector<std::string>> fileData;
        bool isM(const std::string& str);
        bool isNotM(const std::string& str);
        bool isMaster(const  structs::CORPUS corpus);

        std::string join( const std::vector<std::string>& elements, const std::string& endappend);
        const std::string M,separator,endline;

        inline bool isInteger(const std::string & s)
        {
           if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
           char * p ;
           strtol(s.c_str(), &p, 10) ;
          return (*p == 0) ;
        }
    private:

};

#endif // FILE_IO_H
