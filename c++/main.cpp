#include <iostream>

#include "controller.h"

int main(int argc, const char ** argv)
{
    structs::nextData nextData;

    controller mc = controller(argc, argv);
    std::cout << "Controller created!" << std::endl;

    return mc.run();


//    std::string in = "./c++/input.txt";
//
//    bool carryon = false;
//
//    carryon = mc.set_setting();
//
//    int numsettings = mc.get_number_of_runs();
//
//    for( auto i = 0 ; i < numsettings; ++i)
//    {
//        std::cout << std::endl;
//        std::cout << "!!!!!!!!!!!!" << std::endl;
//        std::cout << "Iteration " << i+1 << std::endl;
//        std::cout << std::endl;
//
//        if( i == 0 )
//          carryon = mc.set_next_infile_master();
//
//        if(carryon)
//            carryon = mc.findNextNgrams(i);
//        if(carryon)
//            carryon = mc.set_next_infile_outFile();
//    }

    return 0;
}
