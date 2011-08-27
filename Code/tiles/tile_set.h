#ifndef AURORA_TILES_TILE_SET_H
#define AURORA_TILES_TILE_SET_H

namespace aurora {
namespace tiles {

class Map;
class TileEngine;
class Tile;

class TileSet {
 friend Map;
 friend TileEngine;
 public:
   TileSet(int width,int height,int tile_width,int tile_height);
   ~TileSet();
   //void Initialize(int width,int height,int tile_width,int tile_height);
   //void Deinitialize();
   //void Draw();
 private:
  int tile_width_;
  int tile_height_;
  int width_;
  int height_;
  //Texture* texture_;

  Tile* tile_list;
  //Buffer<gl_c4ub_v2f>* vbo;
  //.Buffer<unsigned short>* ibo;



};

}
}

#endif