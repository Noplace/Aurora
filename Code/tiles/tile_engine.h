#ifndef UISYSTEM_GRAPHICS_TILE_ENGINE_TILE_ENGINE_H
#define UISYSTEM_GRAPHICS_TILE_ENGINE_TILE_ENGINE_H

#include "../opengl.h"
#include "../buffer.h"
#include "../texture_manager.h"

namespace graphics {
namespace tile_engine {
class Map;
class TileEngine;
class TileSet;
class Layer;
class Tile;

class TileEngine {
 public:
  TileEngine();
  ~TileEngine();
  Map* LoadTMX(char* filename);
 private:
  TextureManager* texture_manager;

};

}
}

#include "tile.h"
#include "layer.h"
#include "tile_set.h"
#include "map.h"




#endif