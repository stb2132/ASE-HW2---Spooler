#include <fstream>
#include <sstream>
#include "spool_helper.h"

#define METADATA "/spool/meta"

class mData{

    public:
	mData();
	std::string get_next_id(){return std::to_string(this->id++);}
	std::string create_psuedorandom_fname();
    private:
	int id;

};



