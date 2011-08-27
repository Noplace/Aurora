#ifndef AURORA_TILES_LAYER_H
#define AURORA_TILES_LAYER_H

namespace aurora {
namespace tiles {

class Map;
class Tile;
class TileEngine;

class Layer {
 friend Map;
 friend TileEngine;
 public:
  Layer():width_(0),height_(0),tile_width_(0),tile_height_(0),buffer_offset_(0),show_(true) {}
  ~Layer() { }
  int Initialize(Map* map,int width,int height,int tile_width,int tile_height);
  int Deinitialize();
  graphics::shape::Vertex* CreateVertices();
  int Construct();
  int Draw();
  int width() { return width_; }
  int height() { return height_; }
  int buffer_offset() { return buffer_offset_; }
  void set_buffer_offset(int buffer_offset) { buffer_offset_ = buffer_offset; }
  bool show() { return show_; }
  bool set_show(bool show) { show_ = show; }
 private:
  Map* map_;
  int width_;
  int height_;
  int tile_width_;
  int tile_height_;
  int buffer_offset_;
  int vertex_count_;
  Tile* tile_list;
  bool show_;
  //Buffer<gl_c4ub_v2f>* vbo;
};

}
}

#endif