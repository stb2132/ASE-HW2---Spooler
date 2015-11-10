#include <iostream>
#include "addqueue.h"
#include "queuehelper.h"


int validate_file(fs::path p){
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

int main(int argc, char *argv[]){

    if(argc < 2){
      std::cout << "Please run the command as '$ addqueue <arguments>'." << std::endl;
    } else{

      //Do not want to copy the executable with arguments, so argv+1
      std::vector<std::string> files(argv+1, argv + argc);

      //Main body of work. Here we will validate files, create new names, and move the files
      for(std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it){
	  fs::path p (*it);
          if(validate_file(p) == 0){
              fs::copy_file(p, SPOOL); 
              std::cout << *it << std::endl;
          } else {

          }
      }
    }

    //list_dir("test");

    return 0;

}
