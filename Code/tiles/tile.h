#ifndef AURORA_TILES_TILE_H
#define AURORA_TILES_TILE_H

namespace aurora {
namespace tiles {

class TileSet;
class TileEngine;

class Tile {
 friend TileSet;
 friend TileEngine;
 public:
  Tile() {}
  ~Tile() {}
 private:
  float x,y;
  float w,h;
  //float u,v;
  //float uw,vh;
};

}
}

#endif