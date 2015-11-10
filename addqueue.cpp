#include <iostream>
#include "addqueue.h"
#include "queuehelper.h"


int copyfile(std::string src, std::string dest){


    return 0;
}

int validatefile(std::string name){

    return 0;

}

int drop_priv_temp(uid_t new_uid){
    //if(setresuid(-1, new_uid, geteuid()) < 0){
    //    return ERROR_SYSCALL;
    //}
    //if(geteuid() != new_uid)
    //    return ERROR_SYSCALL;
    return 0;

}

int main(int argc, char *argv[]){

    if(argc < 2){
      std::cout << "Please run the command as '$ addqueue <arguments>'." << std::endl;
    } else{

      //Do not want to copy the executable with arguments, so argv+1
      std::vector<std::string> files(argv+1, argv + argc);

      //Main body of work. Here we will validate files, create new names, and move the files
      for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it){
          std::cout << *it<<std::endl;
      }
    }

    list_dir("test");

    return 0;

}
