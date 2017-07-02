#ifndef OUTPUT_WRITER_H
#define OUTPUT_WRITER_H

#include "file_io.h"

class output_writer : public file_io
{
    public:
        output_writer();
        virtual ~output_writer();

        //bool write_cutOutputFile(const std::vector<structs::ngram_data>&  probData, const std::string& fn);
        bool write_cutOutputFile(const structs::data& data);
        bool write_outputFile(const structs::data& data);

    protected:

    private:

        bool write_output_file(const std::vector<structs::ngram_data>& probData,const std::string& outfile,int maxEntries);

};

#endif // OUTPUT_WRITER_H
