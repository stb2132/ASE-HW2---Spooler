#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS

#include <boost/version.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <ctime>
#include <map>
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <sys/stat.h>

#define SPOOL "/spool/"
#define METADATA SPOOL "meta"
#define TIME_FORMAT "%Y-%m-%d_%H:%M:%S"
#define FILE_NAME "file_"
#define FILE_ID "fileid_"

namespace fs = boost::filesystem;
typedef std::multimap<std::time_t, fs::path> result_map;

class sHelper{
    public:
        int drop_priv_temp(uid_t new_uid);
        int restore_priv();
        std::string format_time(std::string format, time_t time);
        bool validate_file(fs::path p);
        std::string extract_number(std::string name);
        void read_meta_file();
	std::string get_next_id(){return std::to_string(this->id++);}
        void decrement_id(){this->id--;}
        uid_t get_file_owner(std::string filepath);
        void write_last_id();
       
    private:
        int id;
        uid_t p_runner;
};
