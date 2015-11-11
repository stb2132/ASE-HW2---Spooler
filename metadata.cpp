#include "metadata.h"

mData::mData(){
    fs::path p(METADATA);
    if(exists(p)){
        std::ifstream infile(METADATA);
        std::string line;

        std::getline(infile, line);
        //TODO: Add error checking
        this->id = atoi(line.c_str());

        while(std::getline(infile, line)){
            std::istringstream iss(line);
        }
    } else {
        std::ofstream outfile(p.string());
        outfile << "0" << std::endl;
        outfile.close();
        this->id = 0;
    }

}

