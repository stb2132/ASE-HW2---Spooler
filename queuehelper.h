#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <map>

namespace fs = boost::filesystem3;

int list_dir(std::string src){
    typedef std::multimap<std::time_t, fs::path> result_map;
    fs::directory_iterator end_iter;
    result_map map;
    fs::path p (src);
    std::time_t last_write;

    try{
        if(exists(p)){
            if(is_directory(p)){
                //for(auto& entry : boost::make_iterator_range(directory_iterator(p), {} )){
                for(fs::directory_iterator dir_iter(p); dir_iter != end_iter ; ++dir_iter){
                    if(fs::is_regular_file(dir_iter->status()) ){
                        map.insert(result_map::value_type(fs::last_write_time(dir_iter->path()), *dir_iter)); 
                    }
                }
                for(result_map::iterator it = map.begin(); it != map.end(); ++it){
                    std::cout << it->first << " " << it->second << std::endl;
                }
            } else {
                std::cout << "noooo" << std::endl;
            }
        }

    } catch(const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
    }
    return 0;
}
