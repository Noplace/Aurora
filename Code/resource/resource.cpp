#include <string.h>
#include <fstream>
#include "resource.h"
#include "resource_manager.h"


namespace aurora {
namespace resource {

int Resource::ReadWholeFile() {
   
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

  return S_OK;
}

int Resource::DeallocateMemory() {
  if (HeapFree(manager_->heap(),0,data_pointer)==0)
    return S_OK;
  else
    return S_FALSE;
}

bool Resource::Load() {
  if (loaded_ == true) 
    return false;
 
  if (ReadWholeFile() == S_OK) {
    loaded_ = true;
    return true;
  } else {
    return false;
  }
}

bool Resource::Unload() {
  if (loaded_ == false) 
    return false;
  if (DeallocateMemory() == S_OK) {
    loaded_ = false;
    return true;
  } else {
    return false;
  }

}

void Resource::set_filename(const char* filename) { 
  strcpy_s<1024>(filename_,filename); 
}

}
}
