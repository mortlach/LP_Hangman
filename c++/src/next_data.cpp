#include <iostream>
#include <algorithm>
#include <fstream>

#include "next_data.h"
#include "ngram_count_map.h"


next_data::next_data()
{
    //ctor
}

next_data::~next_data()
{
    //dtor
}

bool next_data::get_next_data(structs::data& data, int part)
{
    // for efficience we hvae to read the file and sort as we go


    bool checkForMaster = isMaster(data.nextData.corpus);
    counter = 0;
    bool carryOn = false;

    // reads fn, assuming it a space seperated n-gram data
    // pus each line, split by " " in fileData

    //std::cout << "read_file "<<  fn << std::endl;
    std::vector<std::string> linedata;
    std::string line;
    // Open the stream and read data
    std::ifstream is(data.processedStartingData[part].file);
    if(is)
    {
        //std::cout << "opened " <<  fn << std::endl;
        std::string rawdata((std::istreambuf_iterator<char>(is)),
                            std::istreambuf_iterator<char>());
        //std::cout << rawdata << std::endl;
        std::istringstream rawdatass(rawdata);
        while(std::getline(rawdatass, line))
        {
            linedata.clear();
            //std::cout << line << std::endl;
            split_by_blank(line,linedata);
//            fileData.push_back(linedata);
            for(auto word1it : data.processedStartingData[part].worddata)
            {
                carryOn = true;
                // if  using master words corpus, check for that
                if(checkForMaster && isNotM(linedata[4]))
                carryOn = false;
                if(carryOn)
                {
                    // check if first words in linedata match last words in word1it
                    // and keep the ones which do
                    carryOn = words_match(word1it,linedata,data.nextData.numWords2Match);
                    if(carryOn)
                    {
                        update_finalDataToKeep(word1it, linedata,data);
                    }
                }
            }//for(auto word1it : inputdata.worddata)
        }
        std::sort(data.nextData.probData.begin(), data.nextData.probData.end());

        //std::cout << "read_file found " << fileData.size() << " lines in " << fn << std::endl;
        return true;
    }
    else
        std::cout << "ERROR opening n-gram data " << data.processedStartingData[part].file << std::endl;
    return false;
}
//______________________________________________________________________________
bool next_data::get_next_data_OLD(structs::data& data, int part)
{
    bool checkForMaster = isMaster(data.nextData.corpus);
    counter = 0;
    // iterate through processedStartingData
    // keeping any that match any words match as you go
    // for  words that match (input data and filedata)
    // then  add to the Full string and the list of top 100 FOMs
    bool carryOn = read_ngram_data_file(data.processedStartingData[part].file);
    //std::cout << "get_next_data fileData.size() = " << fileData.size() << std::endl;
    //std::cout << "carryOn  = " << carryOn << std::endl;
    if(carryOn)
    {
        for(auto&& line: fileData)
        {
            // iterate over each worddata from the input file to see if any match
            for(auto word1it : data.processedStartingData[part].worddata)
            {
                carryOn = true;
                // if  using master words corpus, check for that
                if(checkForMaster && isNotM(line[4]))
                    carryOn = false;
                if(carryOn)
                {
                    // check if first words in line match last words in word1it
                    // and keep the ones which do
                    carryOn = words_match(word1it,line,data.nextData.numWords2Match);
                    if(carryOn)
                    {
                        update_finalDataToKeep(word1it, line,data);
                    }
                }
            }//for(auto word1it : inputdata.worddata)
        }//for(auto&& line: fileData)
    }
    return carryOn;
}
//______________________________________________________________________________
//______________________________________________________________________________
bool next_data::remove_probData_duplicates(structs::data& data)
{
    std::sort(data.nextData.probData.begin(), data.nextData.probData.end());
    structs::message("start");
    auto it = data.nextData.probData.begin();
    while(true)
    {
        if( it == data.nextData.probData.end())
        {
            break;
        }
        auto it2 = ++it;
        if( it2 == data.nextData.probData.end())
        {
            break;
        }
        if( it->phrase == it2->phrase)
        {
            it = data.nextData.probData.erase(it);
            //structs::message("del");
        }
        else
        {
            ++it;
        }
    }
    //structs::message("fin");
    return true;
}
//______________________________________________________________________________
bool next_data::words_match(std::vector<std::string>& word1it,
                            std::vector<std::string>& line, int numWords2Match)
{
    bool wordsmatch = false;
    switch(numWords2Match)// oh yeah - we're doing it this way
    {
        case 1:
            if(*(word1it.end() - 3) == line[0])
                wordsmatch = true;
            break;
        case 2:
            if(*(word1it.end() - 4) == line[0])
                if(*(word1it.end() - 3) == line[1])
                     wordsmatch = true;
            break;
        case 3:
            if(*(word1it.end() - 5) == line[0])
                if(*(word1it.end() - 4) == line[1])
                    if(*(word1it.end() - 3) == line[2])
                        wordsmatch = true;
            break;
    }
    return wordsmatch;
}
//______________________________________________________________________________
bool next_data::update_finalDataToKeep(const std::vector<std::string>& word1it,
                                       const std::vector<std::string>& fileline,
                                       structs::data& data)
{
    bool r = false;
    // temp vector for results
    std::vector<std::string> vs;
    // based on numWords2Match how many entires to count-back
    int countfromend = 2 + data.nextData.numWords2Match;//MAGIC_NUMBER
    // copy eh data we want to keep into vs
    vs.insert( vs.end(), word1it.begin(), word1it.end() -countfromend );
    vs.insert( vs.end(), fileline.begin(), fileline.end()-1 );//MAGIC_NUMBER
    // the prob variable is based on the the valeus for both phrases we are joining

    // check if it exists

    std::string temp = join(vs,"");

    if( is_phrase_NOT_in_probData(data,temp) )
    {
        // add a new struct to probData, to hold the new data
        // RENAME probData
        data.nextData.probData.push_back(structs::ngram_data());
        // set the phrase from vs
        data.nextData.probData.back().phrase = join(vs,"");
        // get the probablities, and add to struct
        data.nextData.probData.back().prob = get_probability(data.nextData.ngramCounts,fileline.back());
        r = true;
    }
    return r;
}
//______________________________________________________________________________
bool next_data::is_phrase_in_probData(structs::data& data,const std::string& temp)
{
// try checking if phrase is in pobData here, instead of later in the program
    for(auto i : data.nextData.probData)
    {
        if( i.phrase == temp)
            return true;
    }
    return false;

//    probablities don't add riht when combining phrases
//    als ocan we do it any faster?
}
//______________________________________________________________________________
bool next_data::is_phrase_NOT_in_probData(structs::data& data,const std::string& temp)
{
    return !is_phrase_in_probData(data,temp);
}
//______________________________________________________________________________
double next_data::get_probability(const std::string& ngram, const std::string& count)
{
    double finalvalue = -999.999;//MAGIC_NUMBER
    double phrasecount,value;
    double total_counts;
    bool passed_double = true;
    // if its an integer, its from a data before we
    // move to log probabilitites, so handled
    // slightly different
    if(isInteger(count))
    {
        //std::cout << "count is integer " << std::endl;
        phrasecount = (double)stoi(count);
        passed_double = false;
    }
    else
    {
        double phrasecount = stod (count);
    }
    //std::cout << "Looking for " << ngram <<  std::endl;
    // does this n-gram exists? (it should)
    // find the total counts for that dataset, to normalize probability
    auto it = data::ngramcountmap.find(ngram);
    if(it != data::ngramcountmap.end() )
    {
        total_counts = (double)(it->second);
        value = log10 ( phrasecount/ total_counts );
        // combine values if required to give finalvalue
        if(passed_double)
        {
            finalvalue = value + phrasecount;
        }
        else
        {
            finalvalue = value;
        }
        //ret = true;
    }
    else
    {
        std::cout << "ERROR! ngram = " << ngram << " not found in ngramcountmap " << std::endl;
    }
    //std::cout << "phrasecount = " << phrasecount << "  total_counts = " <<  total_counts
              //<< " frac = " << (double)frac << " Log10(P) = " << value
              //<< " finalvalue = " << finalvalue <<  std::endl;
    return finalvalue;
}
//______________________________________________________________________________

