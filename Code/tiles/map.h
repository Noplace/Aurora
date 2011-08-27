#ifndef AURORA_TILES_MAP_H
#define AURORA_TILES_MAP_H

#include <vector>

namespace aurora {
namespace tiles {

class TileEngine;
class Layer;

class Map : public graphics::shape::Shape  {
 friend TileEngine;
 public:
  Map() : layer_count_(0) {}
  ~Map() {}
  int Initialize(graphics::Context* context,int width,int height,int tile_width,int tile_height);
  int Deinitialize();
  int AddLayer();
  int Construct(); 
  int BuildTransform();
  int Draw();
 private:
  unsigned int buffer_offset(int layer) {
    return layer*width_*height_*4;
  }
  std::vector<TileSet*> tilesets;
  std::vector<Layer*> layers;
  int tile_width_;
  int tile_height_;
  int width_;
  int height_;
  int layer_count_;
};

}
}

#endif