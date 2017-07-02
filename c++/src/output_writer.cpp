#include <fstream>
#include <iostream>
#include "output_writer.h"

output_writer::output_writer()
{
    //ctor
}

output_writer::~output_writer()
{
    //dtor
}
//______________________________________________________________________________
bool output_writer::write_output_file(const std::vector<structs::ngram_data>& probData,const std::string& outfile,int maxEntries)
{
    bool success = false;
    std::ofstream out(outfile);
    if(out)
    {
        int counter = 0;
        std::stringstream ss;
        for (auto i = probData.begin(); i != probData.end(); ++i)
        {
            //std::cout << i->prob << " ";
            ss << i->phrase;
            ss << " ";//magic_string
            ss << i->prob;
            ss << "\n";
            out << ss.str();
            if(counter == maxEntries)
                break;
            ss.str("");
            ++counter;
        }
        out.close();
        success = true;
    }
    return success;
}
//______________________________________________________________________________
bool output_writer::write_cutOutputFile(const structs::data& data)
{
    return write_output_file(data.nextData.probData,data.nextData.cutOutFile,data.nextData.maxEntries);
//
//    bool success = false;
//    std::ofstream out(data.nextData.cutOutFile);
//    if(out)
//    {
//        int counter = 0;
//        std::stringstream ss;
//        for (auto i = data.nextData.probData.begin(); i != data.nextData.probData.end(); ++i)
//        {
//            //std::cout << i->prob << " ";
//            ss << i->phrase;
//            ss << " ";//magic_string
//            ss << i->prob;
//            ss << "\n";
//            out << ss.str();
//            if(counter == data.nextData.maxEntries)
//                break;
//            ss.str("");
//            ++counter;
//        }
//        out.close();
//        success = true;
//    }
//    return success;
}
//______________________________________________________________________________
bool output_writer::write_outputFile(const structs::data& data)
{

    return write_output_file(data.nextData.probData,data.nextData.outFile,-1);

//    std::ofstream out(data.nextData.outFile);
//    bool success = false;
//    if(out)
//    {
//        out << data.nextData.finalDataToKeep.str();
//        out.close();
//        success = true;
//    }
//    return success;
}
