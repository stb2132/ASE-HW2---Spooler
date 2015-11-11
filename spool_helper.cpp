#include "spool_helper.h"

int sHelper::drop_priv_temp(uid_t new_uid){
    if(setresuid(-1, new_uid, geteuid()) < 0)
        return errno;
    if(geteuid() != new_uid)
        return errno;
    return 0;
}

int sHelper::restore_priv(){
    uid_t ruid, euid, suid;
    if(getresuid(&ruid, &euid, &suid) < 0)
        return errno;
    if(setresuid(-1, suid, -1) < 0)
        return errno;
    if(geteuid() != suid)
        return errno;
    return 0;
}


std::string sHelper::format_time(std::string format, time_t time){
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

int sHelper::validate_file(fs::path p){
    try{
        if(fs::exists(p)){
            if(fs::is_regular_file(p)){
                return 0; 
	    }
	}
    } catch (const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
    }
    return 1;
}

//This gets the path/time of creation for a given directory
void sHelper::fill_directory_map(fs::path dir_path, result_map &map){
    fs::directory_iterator end_iter;

    for(fs::directory_iterator dir_iter(dir_path); dir_iter != end_iter ; ++dir_iter){
        if(fs::is_regular_file(dir_iter->status()) ){
            map.insert(result_map::value_type(fs::last_write_time(dir_iter->path()), *dir_iter)); 
        }
    }
}

int sHelper::list_dir(std::string src){
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