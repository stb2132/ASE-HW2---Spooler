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

#define SPOOL "/spool"
#define METADATA "/spool/meta"
#define TIME_FORMAT "%Y-%m-%d_%H:%M:%S"
#define FILE_NAME "file"
#define FILE_ID "fileid"

namespace fs = boost::filesystem;
typedef std::multimap<std::time_t, fs::path> result_map;

class sHelper{
    public:
        int drop_priv_temp(uid_t new_uid);
        int restore_priv();
        std::string format_time(std::string format, time_t time);
        int validate_file(fs::path p);
        void fill_directory_map(fs::path dir_path, result_map &map);
        int list_dir(std::string src);
        void read_meta_file();
	std::string get_next_id(){return std::to_string(this->id++);}
    private:
        int id;
};
