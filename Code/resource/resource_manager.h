#ifndef GAME_ENGINE_RESOURCE_RESOURCE_MANAGER_H
#define GAME_ENGINE_RESOURCE_RESOURCE_MANAGER_H

#include <Windows.h>
#include <map>
#include <vector>
#include "../component.h"
#include "resource.h"
#include "font_resource.h"
#include "texture_resource.h"
#include "effect_resource.h"

namespace game_engine {
namespace resource {

class ResourceManager : public Component {
 public:
  ResourceManager();
  ~ResourceManager();
  int UnloadAll();
  bool LoadXml(char* filename);
  template<class T>
  T* GetResourceById(uint32_t uid) {
    std::vector<Resource*>::iterator i;
    for (i = resource_list_.begin(); i!= resource_list_.end(); ++i) {
      T* res = (T*)(*i);
      if (res->uid() == uid) {
        res->Load();
        return res;
      }
    }

    return NULL;
  }
  Resource* GetResourceById(uint32_t uid) {
    return GetResourceById<Resource>(uid);
  }
  HANDLE heap() { return heap_; }
 private:
  unsigned int resource_count_;
  std::vector<Resource*>  resource_list_;
  std::map<int,std::vector<Resource*> > scope_list_;
  HANDLE heap_;
};

}
}
#endif