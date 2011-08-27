#include "tile_set.h"
#include "tile.h"

namespace aurora {
namespace tiles {


TileSet::TileSet(int width,int height,int tile_width,int tile_height):
    width_(width),height_(height),tile_width_(tile_width),tile_height_(tile_height) {

  tile_list = new Tile[width_*height_];
  int index=0;
  float inv_tex_w = 1.0f/(width_*tile_width_);
  float inv_tex_h = 1.0f/(height_*tile_height_);
  for (int i=0;i<height_;++i)
    for (int j=0;j<width_;++j) {
      
      tile_list[index].x = (float)(j*tile_width)*inv_tex_w;
      tile_list[index].y = (float)(i*tile_height)*inv_tex_h;
      tile_list[index].w = (float)tile_width*inv_tex_w;
      tile_list[index].h = (float)tile_height*inv_tex_h;
      index++;
    }
}

TileSet::~TileSet() {
  delete [] tile_list;
}

}
}