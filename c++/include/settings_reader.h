#ifndef SETTINGS_READER_H
#define SETTINGS_READER_H

#include <string>
#include <fstream>
#include <vector>

#include "file_io.h"


class settings_reader : public file_io
{
    public:
        settings_reader();
        virtual ~settings_reader();

        bool read_arguments(int argc, const char ** argv,
                                             structs::data& data,
                                             bool& passedFileName,
                                             bool& ngram_set,
                                             bool& numWords2Match_set,
                                             std::string& settingsFile);

        bool read_settings(structs::data& data,const std::string& fn);

    protected:

    private:

        std::vector<std::string> get_ngram_string_vector(const std::vector<int>& numWords2Match,
                                                         const std::vector<int>& wordcount);


        std::vector<std::string> getKeyVal(const std::string& trimmedLine, const char delim);
        std::vector<int> getIntVector(const std::string& str);
        std::vector<std::string> getStringVector(const std::string& str);

        std::string input,output,cutput,cutoutput,datapath,usecutput,
                    corpus,numwords2match,wordcounts,maxentries,
                    word1not,word2not,word3not,word4not,word5not,
                    word6not,word7not,word8not,word9not,word10not;

        std::string  trimToDelimiter(std::string const & str, const std::string & STOPDELIMITER );
        std::string& trimAllWhiteSpace(std::string& str);

        std::vector<int> wordcount;

        std::vector<std::string> word1notV;
        std::vector<std::string> word2notV;
        std::vector<std::string> word3notV;
        std::vector<std::string> word4notV;
        std::vector<std::string> word5notV;
        std::vector<std::string> word6notV;
        std::vector<std::string> word7notV;
        std::vector<std::string> word8notV;
        std::vector<std::string> word9notV;
        std::vector<std::string> word10notV;

        bool is_ngram(structs::data& data,const std::string& c);






};

#endif // SETTINGS_READER_H
