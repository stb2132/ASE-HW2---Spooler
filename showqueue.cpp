#include "spool_helper.h"

void show_file(result_map::iterator it, uid_t p_runner){
    sHelper sHelp;

    std::string id = sHelp.extract_number(it->second.filename().string());
    std::string time = sHelp.format_time(TIME_FORMAT, it->first); 

    sHelp.restore_priv();
    uid_t owner = sHelp.get_file_owner(it->second.string());
    sHelp.drop_priv_temp(p_runner);

    if(it->second.filename().string() != "meta"){
        std::cout << it->second.filename() << " " << owner << " " << 
            time << " " << id << std::endl;
    }
}

//This gets the path/time of creation for a given directory
void fill_directory_map(fs::path dir_path, result_map &map){
    fs::directory_iterator end_iter;

    for(fs::directory_iterator dir_iter(dir_path); dir_iter != end_iter ; ++dir_iter){
        if(fs::is_regular_file(dir_iter->status()) && dir_iter->path().filename().string() != METADATA){
            map.insert(result_map::value_type(fs::last_write_time(dir_iter->path()), *dir_iter)); 
        }
    }
}

int list_dir(std::string src, uid_t p_runner){
    result_map map;
    fs::path p (src);
    std::time_t last_write;
    sHelper sHelp;

    try{
        if(exists(p)){
            if(is_directory(p)){

                sHelp.restore_priv();
                fill_directory_map(p, map);
                sHelp.drop_priv_temp(p_runner);

                for(result_map::iterator it = map.begin(); it != map.end(); ++it){
                    show_file(it, p_runner);
                }
            }
        }
    } catch(const fs::filesystem_error& ex){
        std::cout << ex.what() << '\n';
    }
    return 0;
}

int main(int argc, char *argv[]){
    sHelper sHelp;
    uid_t p_runner = getuid();
    sHelp.drop_priv_temp(p_runner);

    if(argc > 1){
        std::cout << "This command takes no arguments. Please run as '$ showqueue'." << std::endl;
    }else{
        list_dir(SPOOL, p_runner);
    }
    return 0;
}
