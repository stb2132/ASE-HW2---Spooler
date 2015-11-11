#include "spool_helper.h"

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
      std::string slash = "/";

      sHelp.restore_priv(); 
      sHelp.read_meta_file();
      sHelp.drop_priv_temp(p_runner);
 
      //Main body of work. Here we will validate files, create new names, and move the files
      for(std::vector<std::string>::iterator it = fpaths.begin(); it != fpaths.end(); ++it){
	  fs::path p (*it);
          if((mcode = sHelp.validate_file(p)) == 0){
    	      try{
                  std::string id = sHelp.get_next_id();
                  std::string new_name = FILE_NAME + id;
	          std::string dest = SPOOL + slash + new_name; 

                  sHelp.restore_priv();
                  fs::copy_file(p, dest); 
                  chown(dest.c_str(), p_runner, getgid()); 
                  sHelp.drop_priv_temp(p_runner);
                  
                  std::cout << p.filename() << ": Y " << FILE_ID << id << std::endl;
              } catch (const fs::filesystem_error& ex){
                  std::cout << ex.what() << '\n';
              }
          } else {
              //print_error_message(mcode);
          }
      }
    }
    return 0;
}
