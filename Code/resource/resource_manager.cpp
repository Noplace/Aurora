#include <Windows.h>
#include <fstream>
#include <WinCore/xml/rapidxml/rapidxml.hpp>
#include "resource.h"
#include "texture_resource.h"
#include "resource_manager.h"


namespace game_engine {
namespace resource {

ResourceManager::ResourceManager() {
  heap_ = HeapCreate(0,1024*1024*2,1024*1024*200);
  //HeapAlloc(heap_,
}

ResourceManager::~ResourceManager() {
  std::vector<Resource*>::iterator i;
  for (i = resource_list_.begin(); i!= resource_list_.end(); ++i) {
    Resource* res = (*i);
    res->Unload();
    delete res;
  }
  HeapDestroy(heap_);
}

bool ResourceManager::LoadXml(char* filename) {
  std::string filename_str(filename);
  std::string path = filename_str.substr(0,filename_str.find_last_of('\\')+1);
  
  std::ifstream ifs( filename );
  if ( ! ifs ) {
    return false;
  }

  const std::string file_content( (std::istreambuf_iterator<char>( ifs )), std::istreambuf_iterator<char>() );
  char* text = const_cast<char*>(file_content.c_str());

  rapidxml::xml_document<> doc;
  doc.parse<0>(text);

  rapidxml::xml_node<> *node = doc.first_node();

  if (strcmp(node->name(),"resources")) {
    return false;
  }

  for (rapidxml::xml_node<> *cnode = node->first_node();
      cnode; cnode = cnode->next_sibling()) {

      if (strcmp(cnode->name(),"resource")==0) {

        Type type = Type::RESOURCE_TYPE_NULL;
        Resource* resource = NULL;
        for (rapidxml::xml_attribute<> *attr = cnode->first_attribute(); attr; attr = attr->next_attribute()) {
          if (!strcmp(attr->name(),"type")) {
            type = (Type)atoi(attr->value());
          }
        }

        if (type == Type::RESOURCE_TYPE_GRAPHICS) {
          resource = new TextureResource();
        } else {
          resource = new Resource();
        }

        for (rapidxml::xml_attribute<> *attr = cnode->first_attribute(); attr; attr = attr->next_attribute()) {

          if (!strcmp(attr->name(),"uid")) {
            resource->set_uid(atoi(attr->value()));
          }

          if (!strcmp(attr->name(),"scope")) {
            resource->set_scope(atoi(attr->value()));
          }

          if (!strcmp(attr->name(),"filename")) {
            resource->set_filename(attr->value());
          }

          if (!strcmp(attr->name(),"type")) {
            resource->set_type((Type)atoi(attr->value()));
          }
        }
        resource->set_manager(this);
        resource_list_.push_back(resource);
        //scope_list_[resource.scope()].push_back(&resource_list_.back());


      }
  }
 
  return true;
 
}
/*
template<class T>
T* ResourceManager::GetResourceById(uint32_t uid) {

}*/

}
}