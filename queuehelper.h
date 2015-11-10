#include <boost/filesystem.hpp>
#include <string>
#include <iostream>

namespace fs = boost:filesystem3

int list_dir(std::string src){
    fs::path p (src);
    try{
        if(exists(p)){
            if(is_directory(p)){
                std::cout << "wooo" << std::endl;
            } else {
                std::cout << "noooo" << std::endl;
            }
        }

        std::cout << "this runs" << std::endl;

    } catch(const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
    }
    return 0;

}
