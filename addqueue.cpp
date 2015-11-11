#include "metadata.h"

int main(int argc, char *argv[]){
    
    sHelper sHelp;
    uid_t p_runner = getuid();
    sHelp.drop_priv_temp(p_runner);

    if(argc < 2){
      std::cout << "Please run the command as '$ addqueue <arguments>'." << std::endl;
    } else{
      //Do not want to copy the executable with arguments, so argv+1
      std::vector<std::string> fpaths(argv+1, argv + argc);
      int mcode;
      mData m;
      std::string slash = "/";
      //Main body of work. Here we will validate files, create new names, and move the files
      for(std::vector<std::string>::iterator it = fpaths.begin(); it != fpaths.end(); ++it){
	  fs::path p (*it);
          if((mcode = sHelp.validate_file(p)) == 0){
    	      try{
                  std::string id = m.get_next_id();
	          std::string dest = SPOOL + slash + FILE_NAME + id; 
                  fs::copy_file(p, dest); 
                  std::cout << *it << std::endl;
              } catch (const fs::filesystem_error& ex){
//                  std::cout << p.filename().string() << " X " << ex.m_error_code << '\n';
              }
          } else {
              //print_error_message(mcode);
          }
      }
    }

    return 0;

}
