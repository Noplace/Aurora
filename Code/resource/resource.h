#ifndef GAME_ENGINE_RESOURCE_RESOURCE_H
#define GAME_ENGINE_RESOURCE_RESOURCE_H

#include <WinCore/types.h>
#include <string.h>

namespace game_engine {
namespace resource {

class ResourceManager;

enum Type {
  RESOURCE_TYPE_NULL = 0,
  RESOURCE_TYPE_GRAPHICS = 1,
  RESOURCE_TYPE_MOVIE = 2,
  RESOURCE_TYPE_AUDIO = 3,
  RESOURCE_TYPE_TEXT = 4
};

class Resource  {
 public:
  Resource() : type_(RESOURCE_TYPE_NULL),scope_(0),uid_(0),loaded_(false),data_pointer(NULL),data_length(0),manager_(NULL) {}
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
  virtual ~Resource()  {}
  virtual bool Load();
  virtual bool Unload();
  uint32_t scope() { return scope_; }
  void set_scope(uint32_t scope) { scope_ = scope; }
  void set_uid(uint32_t uid) { uid_ = uid; }
  void set_filename(const char* filename) { strcpy_s<1024>(filename_,filename); }
  ResourceManager* manager() { return manager_; }
  void set_manager(ResourceManager* manager) { manager_ = manager; }
  void set_type(Type type) { type_ = type; }
  Type type() { return type_; }
  char* filename() { return filename_; }
  uint32_t uid() { return uid_; }
  bool loaded() { return loaded_; }
  void* data_pointer;
  uint32_t data_length; 
 protected:
  ResourceManager* manager_;
  Type type_;
  uint32_t scope_;
  uint32_t uid_;
  char filename_[1024];
  bool loaded_;

};

}
}
#endif