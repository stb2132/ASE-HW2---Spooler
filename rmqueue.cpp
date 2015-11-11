#include "spool_helper.h"

int main(int argc, char *argv[]){

    sHelper sHelp;
    uid_t p_runner = getuid();
    sHelp.drop_priv_temp(p_runner);

    if(argc < 2){
        std::cout << "Please run the command as '$ removequeue <arguments>'." << std::endl;
    } else{
        //Do not want to copy the executable with arguments, so argv+1
        std::vector<std::string> fpaths(argv+1, argv + argc);

        for(std::vector<std::string>::iterator it = fpaths.begin(); it != fpaths.end(); ++it){
            std::istringstream ss(*it);
            int x;
            if(ss >> x){
                std::string file_name = FILE_NAME + *it;
                fs::path p (SPOOL + file_name); 
                sHelp.restore_priv();
                if(sHelp.validate_file(p)){
                    if(sHelp.get_file_owner(p.string()) == p_runner){
                        remove(p);  
                        sHelp.drop_priv_temp(p_runner);
                        std::cout << *it << " Y" << std::endl;
                    } else {
                        std::cout << *it << " X you must be the file owner " <<
                            "to remove this file" << std::endl;
                    }
                } else {
                    std::cout << *it << " X is not a file" << std::endl;
                }

            } else {
                std::cout << *it << " X is not a valid argument" << std::endl;
            }

        }

    }

}

