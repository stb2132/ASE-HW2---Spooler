#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <map>

#define TIME_FORMAT "%Y-%m-%d_%H:%M:%S"

namespace fs = boost::filesystem;
typedef std::multimap<std::time_t, fs::path> result_map;

std::string format_time(std::string format, time_t time){
    struct tm *info;
    info = localtime(&time);
    std::string buf;

    buf.resize(20);
    int len = strftime(&buf[0], buf.size(), format.c_str(), info);
    while(len == 0){
        buf.resize(buf.size() * 2);
        int len = strftime(&buf[0], buf.size(), format.c_str(), info);
    }
    buf.resize(len);
    return buf;
}

//This gets the path/time of creation for a given directory
void fill_directory_map(fs::path dir_path, result_map &map){
    fs::directory_iterator end_iter;

    for(fs::directory_iterator dir_iter(dir_path); dir_iter != end_iter ; ++dir_iter){
        if(fs::is_regular_file(dir_iter->status()) ){
            map.insert(result_map::value_type(fs::last_write_time(dir_iter->path()), *dir_iter)); 
        }
    }
}

int list_dir(std::string src){
    result_map map;
    fs::path p (src);
    std::time_t last_write;

    try{
        if(exists(p)){
            if(is_directory(p)){
                fill_directory_map(p, map);
                
                for(result_map::iterator it = map.begin(); it != map.end(); ++it){
                    std::cout << format_time(TIME_FORMAT, it->first) << " " << it->second << std::endl;
                }
	    }
        }

    } catch(const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
    }
    return 0;
}
