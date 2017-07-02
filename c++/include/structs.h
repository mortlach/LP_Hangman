#ifndef _DATA_STRUCTS_H_
#define _DATA_STRUCTS_H_
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "ngram_count_map.h"


namespace structs
{
    struct startData;
    struct ngram_data;
    struct settings;
    struct nextData;


    enum CORPUS{MASTER, DICTIONARY, NOTSET};

    enum POS{VERB, ADVERB};// etc


    struct ngram_data
    {
        ngram_data() : prob(-999999.999999){}
        std::string phrase;
        double      prob;

        bool operator < (const ngram_data& rhs) const {
            return prob > rhs.prob;
        }
    };


    struct settings
    {
        settings() :
            masterInFile("./c++/input.txt"),
            masterOutFile("./c++/output.txt"),
            masterCutOutFile("./c++/cutOutputFile.txt"),
            corpus(NOTSET),
            maxEntries(500),
            numWords2Match(2),
            usecutput(true)
            {}
        std::vector<int> numWords2Match,maxEntries;
        std::vector<std::string> ngrams;
        std::vector<structs::CORPUS> corpus;
        std::string      masterInFile,masterOutFile,masterCutOutFile,ngramDataPath;
        std::vector<bool> usecutput;
        std::vector<std::string> wordsToExclude;
        std::vector<std::string> wordsToInclude;
    };
    // a nextData struct has all the info for
    //
    struct nextData
    {
        nextData() :
            inFile("./c++/input.txt"),
            outFile("./c++/output.txt"),
            cutOutFile("./c++/cutOutputFile.txt"),
            corpus(NOTSET),
            maxEntries(100),
            numWords2Match(2),
            startWordIndex(1)
            //startData(nullptr)
            {}
        // numWords2Match is the number of words to match
        // maxEntries is number of phrase to keep based on FOM
        int         numWords2Match, maxEntries, startWordIndex;
        std::string ngramCounts,outFile,cutOutFile,inFile;
        CORPUS      corpus;
        std::vector<structs::ngram_data> probData;
        //std::stringstream finalDataToKeep;
        //std::vector<structs::startData> startData;
    };

    struct startData
    {
        startData() :
            corpus(NOTSET),
            numWordsToCheck(4)
            {}
        int              numWordsToCheck;
        CORPUS           corpus;
        std::string      letters,file;
        //std::string      ngram;
        std::vector<std::vector<std::string>> worddata;
    };

    struct data
    {
        structs::settings settings;
        structs::nextData nextData;
        std::vector<structs::startData> processedStartingData;
    };

	
    template<typename T = std::string, typename U = std::string, typename V = std::string, typename W = std::string , typename X = std::string  , typename Y = std::string, typename Z = std::string, typename A = std::string  >
    void printMessage(const T p1,const  U p2 = "" , const V p3 = "",const  W p4 = "", const X p5 = "", const Y p6 = "",const Z p7 = "",  const A p8 = "" )
    {
    std::stringstream ss;
    ss << p1 << p2 << p3 << p4 << p5 << p6 << p7 << p8 <<"\n";
    printf(ss.str().c_str() );
    }

	
         template<typename T = std::string, typename U = std::string, typename V = std::string,
              typename W = std::string, typename X = std::string, typename Y = std::string,
              typename Z = std::string, typename A = std::string >
    void message(const T p1,
                 const U p2 = "", const V p3 = "", const W p4 = "",
                 const X p5 = "", const Y p6 = "", const Z p7 = "",
                 const A p8 = "")
    {
    printMessage(p1, p2, p3, p4, p5, p6, p7, p8);
    }



}
#endif