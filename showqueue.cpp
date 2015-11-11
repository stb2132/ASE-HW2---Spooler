#include "spool_helper.h"

int main(int argc, char *argv[]){
    sHelper sHelp;
    uid_t p_runner = getuid();
    sHelp.drop_priv_temp(p_runner);

    if(argc > 1){
        std::cout << "This command takes no arguments. Please run as '$ showqueue'." << std::endl;
    }else{
        sHelp.list_dir(SPOOL);
    }
    return 0;
}
