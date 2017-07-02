#include "ngram_file_finder.h"
#include <fstream>
#include <sstream>
#include <iostream>

ngram_file_finder::ngram_file_finder():
fileMapDataPath("C:\\Users\\djs56\\cic\\c++\\ngram_fetcher\\mapData.txt")
{
    get_map(fileMapDataPath);
}
//______________________________________________________________________________
ngram_file_finder::~ngram_file_finder()
{
    //dtor
}
//______________________________________________________________________________
bool ngram_file_finder::get_files_ngram_letter(const std::string& ngram,const std::string& letters)
{
    ngramFiles.clear();
    return get_files_ngram_letter(ngram,ngramFiles,letters);
}
//______________________________________________________________________________

//______________________________________________________________________________
bool ngram_file_finder::get_files_ngram_letter(const std::string& ngram,
                        std::vector<std::string>& ngramFiles,const std::string& letters)
{
    //std::cout <<"get_files_ngram_letter LETTERS = "  << letters << std::endl;
    //std::cout <<"get_files_ngram_letter ngram = "  << ngram << std::endl;
    std::vector<std::string> temp;
    // get the files with corretc n-gram from the map filemap

    bool ans = get_files_ngram(ngram,temp);
    // loop trough each file and select those that match letters
    for(auto && it : temp )
    {
        //std::cout <<"get_files_ngram_letter Checking " << it  << std::endl;
        if(stringMatch(it,letters,19,letters.length()))// MAGIC_NUMBER
            ngramFiles.push_back(it);
    }
    return ans;
}
//______________________________________________________________________________
bool ngram_file_finder::get_files_ngram(const std::string& ngram)
{
    ngramFiles.clear();
    return get_files_ngram(ngram,ngramFiles);
}
//______________________________________________________________________________
bool ngram_file_finder::get_files_ngram(const std::string& ngram, std::vector<std::string>& ngramFiles)
{
    bool exists = entryExists(ngram,ngramFiles);
    return exists;
}
//______________________________________________________________________________
bool ngram_file_finder::entryExists(const std::string& key, std::vector<std::string>& values)
{
    bool ret = false;
    auto it = fileMap.find(key);
    if(it != fileMap.end() )
    {
        values = it->second;
        //std::cout << "values" << std::endl;
        ret = true;
    }
    return ret;
}
//______________________________________________________________________________
bool ngram_file_finder::stringMatch(const std::string& s1,const std::string& s2, int n1, int n2)
{
    std::string s11 = s1.substr(n1,n2);
    return s11 == s2;
}
//______________________________________________________________________________
bool ngram_file_finder::get_map(const std::string& fn)
{
    std::string line, key;
    std::istringstream iss;
    std::vector<std::string> tokens;
    // Open the stream
    std::ifstream is(fn);
    if(is)
    {
        while( std::getline( is, line ) ) /// Go through, reading file line by line
        {
            tokens.clear();
            split_by_blank(line,tokens);
            key = tokens[0];
            tokens.erase(tokens.begin());
            fileMap[key]=tokens;
        }
        return true;
    }
    return false;
}
