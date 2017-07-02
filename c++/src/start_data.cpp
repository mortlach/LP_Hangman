#include <iostream>
#include <fstream>
#include "start_data.h"

start_data::start_data():
extraEntries(2)
{
    //ctor
}
//______________________________________________________________________________
start_data::~start_data()
{
    //dtor
}
//______________________________________________________________________________
bool start_data::get_input(structs::data& data)
{
    structs::message("Processing Input file ", data.nextData.inFile);
    // read file data
    bool processed = read_ngram_data_file(data.nextData.inFile);
    // process to get letters and words to match
    if(processed)
        processed =  process_start_data(data);
    if(processed)
    {
        // now check there are ngram files with macthing letters and ngramCounts
        // rease entries that have no file
        std::string filepath;
        for(auto it = data.processedStartingData.begin() ; it != data.processedStartingData.end(); )
        {
            // the path to a file (if it were to exist)
            filepath = data.settings.ngramDataPath +
                       it->letters + "/" +
                       it->letters + "_" +
                       data.nextData.ngramCounts + ".txt";

            // Check if expected filepath exists
            // if it exists: add filepath to data
            // if NOT exists: delete entire entry from processedStartingData

            //structs::message("Looking for filepath ", filepath);
            std::ifstream infile(filepath);
            processed = infile.good();
            if(processed)
            {
                it -> file = filepath;
                //structs::message("found ", it -> file);
                ++it;
            }
            else
            {
                structs::message(filepath, " not found, deleting entry: ",it->letters);
                it = data.processedStartingData.erase(it);
            }
        }

    }
    structs::message("Processed input file");
    if(data.processedStartingData.size()>0)
        return true;
    else
        return false;
}

//______________________________________________________________________________
bool start_data::process_start_data(structs::data& data)
{
    // we take data from the end, depending on numwordstocheck
    // we have multiple first words as well, i.e. ,the, things,
    // are both in the the same file: "th"
    if( file_data_is_good() )
    {
//        count backwards from end of n-gram data the offset of extraEntries (2)
//        is because we have an M or D flag and a count or probability number
//        at the end of each line of n-gram data countfromend is how many
//        entries to count back from .end()
        int countfromend = extraEntries + data.nextData.numWords2Match;

        // get the letters fo the first word
        std::string currentLetters = get_letters(*(fileData[0].end() - countfromend));

        data.processedStartingData.clear();

        add_to_processedStartingData(data,currentLetters,fileData[0]);

        std::cout << "Added " << currentLetters;

        std::string newLetters;
        bool addedtoexistinstruct = false;
        for( auto i = 1 ; i < fileData.size(); ++i )
        {
            newLetters = get_letters(*(fileData[i].end()-countfromend));
            // check if newLetters are already in processedStartingData
            for(auto && it : data.processedStartingData)
            {
                 if(it.letters == newLetters)
                 {
                     // a hit, add to worddata
                     it.worddata.push_back(fileData[i]);
                     // set flag
                     addedtoexistinstruct = true;
                 }
            }
            if(!addedtoexistinstruct)
            {
                // newLetters are not in processedStartingData
                //
                currentLetters = newLetters;
                add_to_processedStartingData(data,currentLetters,fileData[i]);
                std::cout << ", " << newLetters;
            }
            // reset flag
            addedtoexistinstruct = false;
        }
        std::cout << ", " << data.processedStartingData.size() << " sets" << std::endl;
        return true;
    }
    return false;
}
//______________________________________________________________________________
bool start_data::file_data_is_good()
{
    return fileData.size() > 0 && fileData[0].size() >= 6; // Magic_Numbers
}
//______________________________________________________________________________
std::string start_data::get_letters(const std::string& word)
{
    std::string l;
    if(word.length() ==1)
    {
        l = word;
        l.append("_");
    }
    else
    {
        l =  word.substr(0,2);
    }
    return l;
}
//______________________________________________________________________________
void start_data::add_to_processedStartingData(structs::data& data,
                                              const std::string& letters,
                                              const std::vector<std::string>& worddata)
{
    // add new struct
    data.processedStartingData.push_back(structs::startData());
    // set fiorst two letters this word
    data.processedStartingData.back().letters = letters;
    // how many words we are checking
    data.processedStartingData.back().numWordsToCheck = data.nextData.numWords2Match;
    // words to match
    data.processedStartingData.back().worddata.push_back(worddata);
}



