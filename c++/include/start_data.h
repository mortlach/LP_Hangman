#ifndef START_DATA_H
#define START_DATA_H

#include "file_io.h"
#include "structs.h"

class start_data : public file_io
{
    public:
        start_data();
        virtual ~start_data();
        bool get_input(structs::data& data);

    protected:
    private:
        bool process_start_data(structs::data& data);
        bool file_data_is_good();
        std::string get_letters(const std::string& word);
        int extraEntries;
        void add_to_processedStartingData(structs::data& data,
                                          const std::string& letters,
                                          const std::vector<std::string>& worddata);

};
#endif // START_DATA_H
