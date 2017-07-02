#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "ngram_file_finder.h"
#include "settings_reader.h"
#include "next_data.h"
#include "start_data.h"
#include "output_writer.h"

class controller
{
    public:
        controller(int argc, const char ** argv);
        virtual ~controller();

        bool run();

        // set input files directly
        bool set_next_infile_master();
        bool set_next_infile_outFile();
        bool set_next_infile_cutOutFile();

        //bool set_setting();
        int  get_number_of_runs(){return data.settings.ngrams.size();}
        bool findNextNgrams(int part);

    protected:

    private:

        settings_reader   settingsReader;
        start_data        startData;
        next_data         nextData;
        output_writer     outputWriter;

        bool set_nextData(structs::data& data, int part);
        bool get_input();
        bool get_next_data();
        bool write_data();
        bool clean_data_for_next();
        bool using_cutput(size_t part);

        bool passedFileName,ngram_set,numWords2Match_set,arguments_read;
        std::string settingsFile;
        structs::data data;
};

#endif // CONTROLLER_H
