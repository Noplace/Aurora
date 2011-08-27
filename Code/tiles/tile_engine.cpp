#include "tile_engine.h"
#include "../../utilities/rapidxml/rapidxml.hpp"
#include <fstream>

#define set_color(v,r1,g1,b1,a1) v.r = r1; v.g = g1; v.b = b1; v.a= a1;




namespace graphics {
namespace tile_engine {


TileEngine::TileEngine() {
  texture_manager = new TextureManager();
}

TileEngine::~TileEngine() {
  delete texture_manager;
}

void get_map_attributes(rapidxml::xml_node<>* node,int& width,int& height,int& tilewidth,int& tileheight) {
  for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {

    if (!strcmp(attr->name(),"width")) {
      width = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"height")) {
      height = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"tilewidth")) {
      tilewidth = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"tileheight")) {
      tileheight = atoi(attr->value());
    }
    
  }
}

void get_tileset_attributes(rapidxml::xml_node<>* node,int& firstgid,char* name,int& tilewidth,int& tileheight) {
  for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {

    if (!strcmp(attr->name(),"firstgid")) {
      firstgid = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"name")) {
      name = attr->value();
    }

    if (!strcmp(attr->name(),"tilewidth")) {
      tilewidth = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"tileheight")) {
      tileheight = atoi(attr->value());
    }
    
  }
}

void get_layer_attributes(rapidxml::xml_node<>* node,char* name,int& width,int& height) {
  for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()) {

    if (!strcmp(attr->name(),"name")) {
      name = attr->value();
    }

    if (!strcmp(attr->name(),"width")) {
      width = atoi(attr->value());
    }

    if (!strcmp(attr->name(),"height")) {
      height = atoi(attr->value());
    }
    
  }
}

Map* TileEngine::LoadTMX(char* filename) {

  std::string filename_str(filename);
  std::string path = filename_str.substr(0,filename_str.find_last_of('\\')+1);
  
  std::ifstream ifs( filename );
  if ( ! ifs ) {
  }

  const std::string file_content( (std::istreambuf_iterator<char>( ifs )), std::istreambuf_iterator<char>() );
  char* text = const_cast<char*>(file_content.c_str());

  rapidxml::xml_document<> doc;
  doc.parse<0>(text);

  rapidxml::xml_node<> *node = doc.first_node();

  if (strcmp(node->name(),"map")) {
    return NULL;
  }

  int map_width;
  int map_height;
  int map_tw;
  int map_th;
  get_map_attributes(node,map_width,map_height,map_tw,map_th);
  


  Map* map = new Map(map_width,map_height,map_tw,map_th);

  for (rapidxml::xml_node<> *cnode = node->first_node();
      cnode; cnode = cnode->next_sibling())
  {
     if (!strcmp(cnode->name(),"tileset")) {
      int tileset_w,tileset_h,tileset_tw,tileset_th,firstgid;
      char* name=NULL;
      get_tileset_attributes(cnode,firstgid,name,tileset_tw,tileset_th);
      char* image_filename = cnode->first_node()->first_attribute("source")->value();
      std::string image_filename_str(path);
      image_filename_str.append(image_filename);
      Texture* texture;
      texture_manager->CreateTextureFromFile((char*)image_filename_str.c_str(),&texture);
      tileset_w = texture->width()/tileset_tw;
      tileset_h = texture->height()/tileset_th;
      TileSet* tile_set = new TileSet(tileset_w,tileset_h,tileset_tw,tileset_th);
      tile_set->texture_ = texture;
      map->tilesets.push_back(tile_set);
    }
    if (!strcmp(cnode->name(),"layer")) {
      char* name = NULL;
      int layer_w,layer_h;
      get_layer_attributes(cnode,name,layer_w,layer_h);
      Layer* layer = new Layer(layer_w,layer_h,map_tw,map_th);
      
      rapidxml::xml_node<>* tile_node = cnode->first_node()->first_node();

      int index=0;
      gl_c4ub_v2f* vdata = layer->vbo->Lock();
      int lx=0;int ly=0;
      while ( tile_node != NULL) {
        int gid = atoi(tile_node->first_attribute("gid")->value());

        vdata[index+0].x = (float)lx;
        vdata[index+0].y = (float)ly;
        vdata[index+1].x = (float)(lx+map_tw);
        vdata[index+1].y = (float)ly;
        vdata[index+2].x = (float)(lx+map_tw);
        vdata[index+2].y = (float)(ly+map_th);
        vdata[index+3].x = (float)lx;
        vdata[index+3].y = (float)(ly+map_th);

        if (gid == 0) {
          set_color(vdata[index+0],0,0,0,0);
          set_color(vdata[index+1],0,0,0,0);
          set_color(vdata[index+2],0,0,0,0);
          set_color(vdata[index+3],0,0,0,0);
        } else {

          gid -= 1;//firstgid
          Tile*tile = &map->tilesets[0]->tile_list[gid];

          set_color(vdata[index+0],255,255,255,255);
          set_color(vdata[index+1],255,255,255,255);
          set_color(vdata[index+2],255,255,255,255);
          set_color(vdata[index+3],255,255,255,255);

          vdata[index+0].u = tile->x;
          vdata[index+0].v = tile->y;
          vdata[index+1].u = (tile->x+tile->w);
          vdata[index+1].v = tile->y;
          vdata[index+2].u = (tile->x+tile->w);
          vdata[index+2].v = (tile->y+tile->h);
          vdata[index+3].u = tile->x;
          vdata[index+3].v = (tile->y+tile->h);
        }
        index+=4;
        
        lx += map_tw;
        if (lx == (layer_w*map_tw)) {
          lx = 0;
          ly += map_th;
        }

        tile_node = tile_node->next_sibling();
      }
      layer->vbo->Unlock();

      map->layers.push_back(layer);
    }
  }

    


  return map;

}



}
}