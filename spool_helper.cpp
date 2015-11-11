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

bool sHelper::validate_file(fs::path p){
    try{
        if(fs::exists(p)){
            if(fs::is_regular_file(p)){
                return true; 
            }
        }
    } catch (const fs::filesystem_error& ex){
        std::cout << "this ran" << std::endl;
        std::cout << ex.what() << '\n';
    }
    return false;
}

uid_t sHelper::get_file_owner(std::string filepath){
    struct stat info;
    stat(filepath.c_str(), &info);
    return info.st_uid;
}

std::string sHelper::extract_number(std::string name){
    std::string delim = "_";
    std::string number = name.substr(name.find_last_of(delim)+1);
    return number;
}

void sHelper::write_last_id(){
    std::string pname = METADATA;
    std::ofstream outfile(pname);
    outfile << this->id << std::endl; 
}

void sHelper::read_meta_file(){
    std::string pname = METADATA;
    fs::path p(pname);
    if(exists(p)){
        std::ifstream infile(pname);
        std::string line;

        std::getline(infile, line);
        //TODO: Add error checking
        this->id = atoi(line.c_str());

    } else {
        std::ofstream outfile(p.string());
        outfile << "0" << std::endl;
        outfile.close();
        this->id = 0;
    }
}
