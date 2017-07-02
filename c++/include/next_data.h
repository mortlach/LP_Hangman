#ifndef NEXT_DATA_H
#define NEXT_DATA_H

#include "structs.h"
#include "file_io.h"

class next_data : public file_io
{
    //    This class takes in startData finds the correct file
    //    checks the desired words match
    //    joins the input phrases with the selected phrases
    //    and calculates a figure-of-merit (FOM)
    //    it can output all the data, or sorted by FOM

    public:
        next_data();
        virtual ~next_data();

        bool get_next_data(structs::data& data,int part);
        bool get_next_data_OLD(structs::data& data,int part);

        bool remove_probData_duplicates(structs::data& data);


        bool process_line(std::vector<std::string> linedata, structs::data& data);

        int counter;

    protected:

    private:

        bool update_finalDataToKeep(const std::vector<std::string>& word1it,
                                    const std::vector<std::string>& fileline,
                                    structs::data& data);

        double get_probability(const std::string& ngram,
                               const std::string& count);

        bool words_match(std::vector<std::string>& word1it,
                         std::vector<std::string>& line,
                         int numWords2Match);

        bool is_phrase_in_probData(structs::data& data,const std::string& temp);
        bool is_phrase_NOT_in_probData(structs::data& data,const std::string& temp);

};

#endif // NEXT_DATA_H
