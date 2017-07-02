#include "file_io.h"

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

file_io::file_io():
M("M"),
separator(" "),
endline("\n")
{
    //ctor
}

file_io::~file_io()
{
    //dtor
}
//______________________________________________________________________________
bool file_io::isM(const std::string& str)
{
    return str == M;
}
//______________________________________________________________________________
bool file_io::isNotM(const std::string& str)
{
    return !isM(str);
}
//______________________________________________________________________________
bool file_io::isMaster(const  structs::CORPUS corpus)
{
    return  corpus == structs::CORPUS::MASTER;
}
//______________________________________________________________________________
bool file_io::read_ngram_data_file(const std::string& fn)
{
    fileData.clear();
    return read_ngram_data_file(fn,fileData);
}
//______________________________________________________________________________
bool file_io::read_ngram_data_file(const std::string& fn, std::vector<std::vector<std::string>>& fileData)
{
    // reads fn, assuming it a space seperated n-gram data
    // pus each line, split by " " in fileData

    //std::cout << "read_file "<<  fn << std::endl;
    std::vector<std::string> linedata;
    std::string line;
    // Open the stream and read data
    std::ifstream is(fn);
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
            fileData.push_back(linedata);
        }
        std::cout << "read_file found " << fileData.size() << " lines in " << fn << std::endl;
        return true;
    }
    else
        std::cout << "ERROR opening n-gram data " << fn << std::endl;
    return false;
}
//______________________________________________________________________________
void file_io::split_by_blank(std::string& line, std::vector<std::string>& tokens)
{
    std::istringstream iss(line);
    split_by_blank(iss,tokens);
}
//______________________________________________________________________________
void file_io::split_by_blank(std::istringstream& iss, std::vector<std::string>& tokens)
{
    std::copy(std::istream_iterator<std::string>(iss),std::istream_iterator<std::string>(),
              std::back_inserter(tokens));
}
//______________________________________________________________________________
std::string file_io::join( const std::vector<std::string>& elements, const std::string& endappend)
{
    switch(elements.size())
    {
        case 0:
            return "";
        case 1:
            return elements[0];
        default:
            std::ostringstream os;
            std::copy(elements.begin(), elements.end()-1, std::ostream_iterator<std::string>(os, separator.c_str()));
            os << *elements.rbegin();
            os << endappend;
            return os.str();
    }
}
//______________________________________________________________________________

