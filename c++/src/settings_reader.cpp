#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>


#include "settings_reader.h"

settings_reader::settings_reader():
input("input"),
output("output"),
cutput("cutput"),
cutoutput("cutoutput"),
datapath("datapath"),
corpus("corpus"),
numwords2match("numwords2match"),
maxentries("maxentries"),
usecutput("usecutput"),
wordcounts("wordcounts"),
word1not("word1not"),
word2not("word2not"),
word3not("word3not"),
word4not("word4not"),
word5not("word5not"),
word6not("word6not"),
word7not("word7not"),
word8not("word8not"),
word9not("word9not"),
word10not("word10not")
{
    //ctor
}

settings_reader::~settings_reader()
{
    //dtor
}

bool settings_reader::read_arguments(int argc, const char ** argv,
                                     structs::data& data,
                                     bool& passedFileName,
                                     bool& ngram_set,
                                     bool& numWords2Match_set,
                                     std::string& settingsFile
                                     )
{
    // hardcoded default values just in case
    data.settings.masterInFile  ="./c++/ngin.txt";
    data.settings.masterOutFile ="./c++/ngout.txt";
    data.settings.masterCutOutFile ="./c++/ngcut.txt";
    data.settings.ngramDataPath = "./ngram_data/4gram/";

    for(auto i = 0; i < argc; i++)
    {
        printf("Argument %i = %s\n", i, argv[i]);

        std::string c = argv[i];
        if(passedFileName)
        {
            settingsFile = c;
        }
        else if(c == "-f")
        {
            passedFileName = true;
        }
        else if(c == "-M")
        {
            data.settings.corpus.push_back(structs::CORPUS::MASTER);
            structs::message("Using master corpus");
        }
        else if(c == "-m")
        {
            data.settings.corpus.push_back(structs::CORPUS::MASTER);
            structs::message("Using master corpus");
        }
        else if(c == "-1")
        {
            data.settings.numWords2Match.push_back(1);
            numWords2Match_set = true;
        }
        else if(c == "-2")
        {
            data.settings.numWords2Match.push_back(2);
            numWords2Match_set = true;
        }
        else if(c == "-3")
        {
            data.settings.numWords2Match.push_back(3);
            numWords2Match_set = true;
        }
        else if(c == "1")
        {
            data.settings.numWords2Match.push_back(1);
            numWords2Match_set = true;
        }
        else if(c == "2")
        {
            data.settings.numWords2Match.push_back(2);
            numWords2Match_set = true;
        }
        else if(c == "3")
        {
            data.settings.numWords2Match.push_back(3);
            numWords2Match_set = true;
        }
        else if(!ngram_set)
        {
             if(is_ngram(data,c))
             {
                ngram_set = true;
                structs::message("ngram_set = ", data.settings.ngrams[0]);
             }
        }
    }
    return true;
}
//______________________________________________________________________________
bool settings_reader::is_ngram(structs::data& data, const std::string& c)
{
    bool r = false;
    auto found = c.find(",");
    if(found!=std::string::npos)
    {
//        std::replace(data.settings.ngrams[0].begin(), data.settings.ngrams[0].end(), '-', '_');
//        std::replace(data.settings.ngrams[0].begin(), data.settings.ngrams[0].end(), ',', '_');
//        std::replace(data.settings.ngrams[0].begin(), data.settings.ngrams[0].end(), '.', '_');
        std::stringstream ss(c);
        int i;
        wordcount.clear();
        while(ss >> i)
        {
            wordcount.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        data.settings.ngrams = get_ngram_string_vector(data.settings.numWords2Match, wordcount);

        if(data.settings.ngrams.size()>0)
            r = true;
    }
    return r;
}
//______________________________________________________________________________
bool settings_reader::read_settings(structs::data& data, const std::string& fn)
{
    structs::message("read_settings, file = ", fn);
    std::ifstream inputFile;
    std::vector<std::string> keyVal;
    inputFile.open(fn, std::ios::in);
    std::string line,trimmedLine;
    bool foundwordcount = false;
    bool foundnumwords2match = false;
    if(inputFile)
    {
        while(std::getline(inputFile, line)) /// Go through, reading file line by line
        {
            //trimmedLine = trimAllWhiteSpace(trimToDelimiter(line, "\n"));

            //structs::message(trimmedLine);

            keyVal.clear();

            keyVal = getKeyVal(line,'=');

            if(keyVal.size() == 2)
            {
                //structs::message("keyVal[0]_", keyVal[0],"_");
                //structs::message("keyVal[1]_", keyVal[1],"_");
                if(keyVal[0] == input)
                {
                    data.settings.masterInFile = keyVal[1];
                    structs::message("input file = ", input);
                }
                else if(keyVal[0] == output)
                {
                    data.settings.masterOutFile = keyVal[1];
                    structs::message("output file = ",data.settings.masterOutFile);
                }
                else if(keyVal[0] == cutput)
                {
                    data.settings.masterCutOutFile = keyVal[1];
                    structs::message("cutput file = ",data.settings.masterCutOutFile);
                }
                else if(keyVal[0] == datapath)
                {
                    data.settings.ngramDataPath = keyVal[1];
                    structs::message("datapath = ",data.settings.ngramDataPath);
                }
                else if(keyVal[0] == corpus)
                {
                    if(keyVal[1] == "m" || keyVal[1] == "M")
                    {
                        data.settings.corpus.push_back(structs::CORPUS::MASTER);
                        structs::message("corpus = master");
                    }
                    else
                        structs::message("corpus = dictionary");
                }
                else if(keyVal[0] == numwords2match)
                {
                    data.settings.numWords2Match = getIntVector(keyVal[1]);
                    structs::message("added numwords2match = ", keyVal[1]);
                    foundnumwords2match = true;
                }
                else if(keyVal[0] == wordcounts)
                {
                    wordcount = getIntVector(keyVal[1]);
                    structs::message("added wordcount = ", keyVal[1]);
                    foundwordcount = true;
                }
                else if(keyVal[0] == maxentries)
                {
                    data.settings.maxEntries = getIntVector(keyVal[1]);
                    foundwordcount = true;
                }
                else if(keyVal[0] == usecutput)
                {
                    std::vector<int> temp = getIntVector(keyVal[1]);
                    structs::message("added usecutput = ",keyVal[1]);
                    for(auto i : temp)
                    {
                        if(i == 1)
                        {
                            data.settings.usecutput.push_back(true);
                            structs::message("added true to usecutput ");
                        }
                        else
                        {
                            data.settings.usecutput.push_back(false);
                            structs::message("added false to usecutput ");
                        }
                    }
                }
                else if(keyVal[0] == maxentries)
                {
                    data.settings.maxEntries = getIntVector(keyVal[1]);
                    foundwordcount = true;
                }
                else if(keyVal[0] == word1not)
                {
                    word1notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word2not)
                {
                    word2notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word3not)
                {
                    word3notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word4not)
                {
                    word4notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word5not)
                {
                    word5notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word6not)
                {
                    word6notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word7not)
                {
                    word7notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word8not)
                {
                    word8notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word9not)
                {
                    word9notV = getStringVector(keyVal[1]);
                }
                else if(keyVal[0] == word10not)
                {
                    word10notV = getStringVector(keyVal[1]);
                }
            }
            else
            {
                structs::message("settings_reader a keyVal.size() != 2");
            }
        }
        if(foundnumwords2match && foundwordcount)
        {
            //structs::message("if(foundnumwords2match && foundwordcount)");
            data.settings.ngrams = get_ngram_string_vector(data.settings.numWords2Match,wordcount);
        }
    }
    if(data.settings.ngrams.size() > 0)
        return true;
    else
        return false;
}
//______________________________________________________________________________
std::vector<std::string> settings_reader::get_ngram_string_vector(const std::vector<int>& numWords2Match,
                                                                  const std::vector<int>& wordcount)
{
    int n = 4; // the n in ngram //MAGIC_NUMBER
    std::string t;
    std::vector<std::string> r;
    std::vector<int> ngram;

    int count;
    int start = 0;
    int it = 0;

//    structs::message("checking wordcount values:");
//    for(auto & it: wordcount)
//    {
//        structs::message(it);
//    }
//    structs::message("parsing wordcount, wordcount.size() = ", wordcount.size());

    // append the next 4 numbers to ngram
    while(true)
    {
        if(it >= numWords2Match.size())
        {
            count = n - numWords2Match.back();
            //structs::message("count =  4 - ", numWords2Match.back()," = ", count);
        }
        else
        {
            count = n - numWords2Match[it];
            //structs::message("count =  4 - ", numWords2Match[it]," = ", count);
            ++it;
        }
        start += count;
        // if we are near the end of wordcount break
        if(start + n > wordcount.size())
        {
            structs::message("Found all NGRAMS, ", start + n, " / ", wordcount.size());
            break;
        }
        //structs::message("NEW start = ", start);
        ngram.clear();
        for(auto i = start; i < start + n; ++i)
        {
            ngram.push_back(wordcount[i]);
            //structs::message("added ", wordcount[i]);
        }
        t = "";
        for(auto i : ngram)
        {
            switch( i ) // cancer
            {
                case -1:
                    t += "._";
                    break;
                default:
                    t += std::to_string(i) + "_";
                    break;
            }
        }
        t.pop_back();
        r.push_back(t);
        structs::message("NEW ngram = ", t);
    }
    return r;
}
//______________________________________________________________________________
std::vector<int> settings_reader::getIntVector(const std::string & str )
{
    std::vector< int > ret;
    std::stringstream ss(str );
    std::string s;
    std::stringstream os;
    int temp;
    while(ss)
    {
        if(!getline(ss, s, ',' ) )
            break;
        else
        {
            //ret.push_back(atof(s.c_str() ) );
            // this way allows you to write numbers in scientific E notation, i.e. 6.3E+3 etc.
            if(s == ".")
                os << -1;
            else
                os << s;
            os >> temp;
            ret.push_back(temp );
            os.clear();
            //structs::message(ret.back(), " ");
        }
    }
//    std::cout << std::endl;
    return ret;
}
//______________________________________________________________________________
std::vector<std::string> settings_reader::getStringVector(const std::string& str)
{
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> r;
    while(std::getline(ss, item, ','))//MAGIC_STRING
    {
        r.push_back(item);
        structs::message("Added ",item);
    }
    return r;
}
//______________________________________________________________________________
std::string settings_reader::trimToDelimiter(std::string const& str, const std::string& STOPDELIMITER )
{
    size_t last = str.find_first_of(STOPDELIMITER );
    return str.substr(0, last );
}
//______________________________________________________________________________
std::string & settings_reader::trimAllWhiteSpace(std::string& str)
{
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}
//______________________________________________________________________________
std::vector<std::string> settings_reader::getKeyVal(const std::string & trimmedLine, const char delim)
{
    std::stringstream ss(trimmedLine);
    std::string item;
    std::vector<std::string> entry;
    while(std::getline(ss, item, delim ) )
        entry.push_back( trimAllWhiteSpace(item) );
//    for(int i = 0; i < entry.size(); ++i )
//        std::cout << "entry "<< i << " = " <<  entry[ i ] << std::endl;
    return entry;
}
//______________________________________________________________________________
