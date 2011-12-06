#ifndef AURORA_RESOURCE_RESOURCE_H
#define AURORA_RESOURCE_RESOURCE_H

#include <WinCore/types.h>

namespace aurora {
namespace resource {

class ResourceManager;

enum Type {
  RESOURCE_TYPE_NULL = 0,
  RESOURCE_TYPE_GRAPHICS = 1,
  RESOURCE_TYPE_MOVIE = 2,
  RESOURCE_TYPE_AUDIO = 3,
  RESOURCE_TYPE_TEXT = 4,
  RESOURCE_TYPE_BMFONT = 5,
  RESOURCE_TYPE_EFFECT = 6,
  RESOURCE_TYPE_OTHER = 100
};

class Resource  {
 public:
  Resource() : type_(RESOURCE_TYPE_NULL),scope_(0),uid_(0),loaded_(false),data_pointer(null),data_length(0),manager_(null) {}
  Resource(const Resource& src) {
    set_scope(src.scope_);
    set_uid(src.uid_);
    set_type(src.type_);
    set_filename(src.filename_);
    set_manager(src.manager_);
    loaded_ = src.loaded_;
    data_pointer = src.data_pointer;
    data_length = src.data_length;
  }
  virtual ~Resource()  {
    DeallocateMemory();
  }
  int ReadWholeFile();
  int DeallocateMemory();
  virtual bool Load();
  virtual bool Unload();
  uint32_t scope() { return scope_; }
  void set_scope(uint32_t scope) { scope_ = scope; }
  void set_uid(uint32_t uid) { uid_ = uid; }
  void set_filename(const char* filename);
  void set_filepath(const char* filepath);
  ResourceManager* manager() { return manager_; }
  void set_manager(ResourceManager* manager) { manager_ = manager; }
  void set_type(Type type) { type_ = type; }
  Type type() { return type_; }
  const char* filename() { return filename_; }
  const char* filepath() { return filepath_; }
  uint32_t uid() { return uid_; }
  bool loaded() { return loaded_; }
  void* data_pointer;
  uint32_t data_length; 
 protected:
  ResourceManager* manager_;
  Type type_;
  uint32_t scope_;
  uint32_t uid_;
  char filename_[256];
  char filepath_[1024];
  bool loaded_;

};

}
}
#endif