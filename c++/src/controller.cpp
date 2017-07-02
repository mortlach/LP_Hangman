#include "controller.h"
#include <iostream>
#include <fstream>
#include <algorithm>

controller::controller(int argc, const char ** argv):
passedFileName(false),
ngram_set(false),
numWords2Match_set(false),
arguments_read(false)
{
    arguments_read = settingsReader.read_arguments(argc, argv, data,
                                                   passedFileName,ngram_set,
                                                   numWords2Match_set,settingsFile);
    if(!arguments_read)
        structs::message("Error in passed arguemnts =  ");
}
//______________________________________________________________________________
controller::~controller()
{
}
//______________________________________________________________________________
bool controller::run()
{
    bool carryon = false;
    if(passedFileName)
    {
        structs::message("settingsFile =  ",settingsFile);
        carryon = settingsReader.read_settings(data, settingsFile);
    }
    else
    {
        if( ngram_set && numWords2Match_set)
            carryon = true;

        //set_setting();
    }

    if(carryon)
    {
        int numsettings = get_number_of_runs();
        for( auto i = 0 ; i < numsettings; ++i)
        {
            if( carryon )
            {
                structs::message("\n!!!!!!!!!!!!\nIteration ",i+1,"\n");
                if( i == 0 )
                  carryon = set_next_infile_master();
                if(carryon)
                    carryon = findNextNgrams(i);
                if(carryon)
                {
                    if(using_cutput(i))
                    {
                        carryon = set_next_infile_cutOutFile();
                        //structs::message("using_cutput returned True");
                    }
                    else
                    {
                        carryon = set_next_infile_outFile();
                        //structs::message("using_cutput returned True");
                    }
                }
            }
        }
    }
    return carryon;
}
//______________________________________________________________________________
bool controller::using_cutput(size_t part)
{
    // if we don't have new vlaues use the last
    if( data.settings.usecutput.size() > part )
        return data.settings.usecutput[part];
    else
        return  data.settings.usecutput.back();
}
//______________________________________________________________________________
//bool controller::set_setting()
//{
//    // first iterations
//
//    data.settings.numWords2Match.clear(); // !! note this too part if run file
//    data.settings.ngrams.clear(); // !! note this too part if run file
//    data.settings.maxEntries.clear();
//    data.settings.corpus.clear();
//
//    data.settings.numWords2Match.push_back(2); // !! note this too part if run file
//    data.settings.ngrams.push_back("6_3_3_5"); // !! note this too part if run file
//    data.settings.maxEntries.push_back(500);
//    data.settings.corpus.push_back(structs::CORPUS::MASTER);
//
//
//    // second iteration, this time match 3 words
//    data.settings.ngrams.push_back("3_3_5_3"); // !! note this too part if run file
//    data.settings.numWords2Match.push_back(3); // !! note this too part if run file
//    data.settings.maxEntries.push_back(500);
//    data.settings.corpus.push_back(structs::CORPUS::MASTER);
//
//    // third iteration, this time match 3 words
//    data.settings.ngrams.push_back("3_5_3_2"); // !! note this too part if run file
//
//    return true;
//}
//______________________________________________________________________________
bool controller::findNextNgrams(int part)
{
    //int part = 0;

    bool carry_on = clean_data_for_next();
    if(carry_on)
        carry_on = set_nextData(data,part);
    if(carry_on)
    {
        carry_on = get_input();
        if(carry_on)
        {
            //structs::message("Found ", data.processedStartingData.size(), " sets");
            carry_on = get_next_data();
            if(carry_on)
            {
                if(outputWriter.write_cutOutputFile(data))
                    structs::message(data.nextData.ngramCounts ," cut data in ",data.nextData.cutOutFile );
                if(outputWriter.write_outputFile(data))
                    structs::message(data.nextData.ngramCounts ," data in  ",data.nextData.outFile );
            }
            else
            {
                structs::message("get_next_data failed");
            }
        }
        else
        {
            structs::message("get_input failed");
        }
    }
    else
    {
        structs::message("set_nextData failed");
    }
    return carry_on;
}
//______________________________________________________________________________
bool controller::set_next_infile_master()
{
    data.nextData.inFile = data.settings.masterInFile;
    //structs::message("new nextData.infile = ",data.nextData.inFile);
    return true;
}
//______________________________________________________________________________
bool controller::set_next_infile_outFile()
{
    data.nextData.inFile = data.nextData.outFile;
    structs::message("new nextData.inFile = ",data.nextData.inFile);
    return true;
}
//______________________________________________________________________________
bool controller::set_next_infile_cutOutFile()
{
    data.nextData.inFile = data.nextData.cutOutFile;
    structs::message("new nextData.inFile = ",data.nextData.inFile);
    return true;
}

//______________________________________________________________________________
bool controller::set_nextData(structs::data& data, int part)
{
    // if we don't have new vlaues use the last
    if( data.settings.numWords2Match.size() > part )
        data.nextData.numWords2Match = data.settings.numWords2Match[part];
    else
        data.nextData.numWords2Match = data.settings.numWords2Match.back();
    if( data.settings.ngrams.size() > part )
        data.nextData.ngramCounts = data.settings.ngrams[part];
    else
        data.nextData.ngramCounts = data.settings.ngrams.back();
    if( data.settings.maxEntries.size() > part )
        data.nextData.maxEntries = data.settings.maxEntries[part];
    else
        data.nextData.maxEntries = data.settings.maxEntries.back();
    if( data.settings.corpus.size() > part )
        data.nextData.corpus = data.settings.corpus[part];
    else
        data.nextData.corpus = data.settings.corpus.back();
    // set file output names
    //data.nextData.cutOutFile = data.settings.masterCutOutFile;
    //data.nextData.outFile    = data.settings.masterOutFile;
    // append a number before the .txt (SHOULD think about changing this)
    std::string s = std::to_string(part+1);


    data.nextData.cutOutFile = data.settings.masterCutOutFile;
    auto p1 = data.nextData.cutOutFile.find_last_of(".", std::string::npos);

    //data.nextData.cutOutFile.insert(p1,*(s.c_str()) ) ;
    data.nextData.cutOutFile.insert(p1, s );

    data.nextData.outFile = data.settings.masterOutFile;
    auto p2 = data.nextData.outFile.find_last_of(".", std::string::npos);
    //data.nextData.outFile.insert(p2,*(s.c_str()));
    data.nextData.outFile.insert(p2, s);

//    if( part+1 > 10 )
//    {
//        data.nextData.cutOutFile.insert(data.settings.masterCutOutFile.end()-5,*(s.c_str())); // MAGIC_NUMBER
//        data.nextData.outFile.insert(data.settings.masterOutFile.end()-5,*(s.c_str())); // MAGIC_NUMBER
//    }
//    else
//    {
//        data.nextData.cutOutFile.insert(data.settings.masterCutOutFile.end()-4,*(s.c_str())); // MAGIC_NUMBER
//        data.nextData.outFile.insert(data.settings.masterOutFile.end()-4,*(s.c_str())); // MAGIC_NUMBER
//    }


    return true;
}
//______________________________________________________________________________
// read the input file
bool controller::get_input()
{
    data.processedStartingData.clear();
     return startData.get_input(data);
}
//______________________________________________________________________________
bool controller::get_next_data()
{
    // iterate through each mathcing n0gram file and look for the nextData
    // nextData are teh phrases tha thave matchign words,
    // plus this function updates the Figure-of-merit
    for( auto i = 0; i < data.processedStartingData.size(); ++i )
    {
        nextData.get_next_data(data,i);
        //structs::message(i);
    }
    // delete dupicate entries,
    // duplicates can happen for a few reasons
    // so wait till here to get rid of them
    structs::message("remove_probData_duplicates ");
    if(data.nextData.probData.size()>1)
    {
        //structs::message("if(data.nextData.probData.size()>0)");
        //bool carryOn = nextData.remove_probData_duplicates(data);
    }
    structs::message("Found ", data.nextData.probData.size(), " matching N-grams");
    if(data.nextData.probData.size() > 0)
        return true;
    else
        return false;
}
//______________________________________________________________________________
bool controller::clean_data_for_next()
{
    data.processedStartingData.clear();
    data.nextData.probData.clear();
    //data.nextData.finalDataToKeep.str("");
    return true;
}
//______________________________________________________________________________
bool controller::write_data()
{
    if(outputWriter.write_cutOutputFile(data))
        return outputWriter.write_outputFile(data);
    return false;
}
