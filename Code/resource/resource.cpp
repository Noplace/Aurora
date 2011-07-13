#include "resource.h"
#include "resource_manager.h"
#include <fstream>

namespace game_engine {
namespace resource {

bool Resource::Load() {
  if (loaded_ == true) 
    return false;
  
  std::ios::openmode mode = std::ios::beg | std::ios::in;
  if (type_ != 4) {
    mode |= std::ios::binary;
  }
  std::ifstream ifs( filename_,mode);
  if (type_ != 4) {
    ifs.seekg(0,std::ios::end);
    data_length = ifs.tellg();
    ifs.seekg(0,std::ios::beg);
    data_pointer = HeapAlloc(manager_->heap(),0,data_length);
    ifs.read((char*)data_pointer,data_length);
  }
  else {
    const std::string file_content( (std::istreambuf_iterator<char>( ifs )), std::istreambuf_iterator<char>() );
    data_length = file_content.length();
    data_pointer = HeapAlloc(manager_->heap(),0,data_length);
    memcpy((char*)data_pointer,file_content.c_str(),data_length);
  }
  
  ifs.close();

  loaded_ = true;
  return true;
}

bool Resource::Unload() {
  if (loaded_ == false) 
    return false;
  HeapFree(manager_->heap(),0,data_pointer);
  loaded_ = false;
  return true;
}

}
}
