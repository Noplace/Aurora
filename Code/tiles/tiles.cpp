#include "tiles.h"


#define set_color(v,r1,g1,b1,a1) v.r = r1; v.g = g1; v.b = b1; v.a= a1;



/*
void TileSet::Initialize(int width,int height,int tile_width,int tile_height) {
  tile_width_  = tile_width;
  tile_height_ = tile_height;
  width_  = width;
  height_ = height;

  tile_list = new Tile[width_*height_];
 
  int index=0;
  for (int i=0;i<height_;++i)
    for (int j=0;j<width_;++j) {
      
      tile_list[index].x = (float)(j*tile_width);
      tile_list[index].y = (float)(i*tile_height);
      tile_list[index].w = (float)tile_width;
      tile_list[index].h = (float)tile_height;
      tile_list[index].u = 16*3;
      tile_list[index].v = 16*2;
      tile_list[index].uw = 16;
      tile_list[index].vh = 16;
      index++;
    }


  vbo = new Buffer<gl_c4ub_v2f>(width_*height_*4);
  //ibo = new Buffer<unsigned short>((width_-1)*(height_-1)*4,GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW);
  gl_c4ub_v2f* vdata = vbo->Lock();

  index=0;
  int tile_index =0;
  for (int i=0;i<width_;++i)
    for (int j=0;j<height_;++j) {
      set_color(vdata[index+0],255,255,255,255);//i+j+40,i*4,j*4,255);
      set_color(vdata[index+1],255,255,255,255);
      set_color(vdata[index+2],255,255,255,255);
      set_color(vdata[index+3],255,255,255,255);
      //vdata[index].x = (float)(i*tile_size_);
      //vdata[index].y = (float)(j*tile_size_);
      //vdata[index].u = ((float)i/(float)width_);
      //vdata[index].v = ((float)j/(float)height_);
      Tile* tile = &tile_list[tile_index];
      vdata[index+0].x = tile->x;
      vdata[index+0].y = tile->y;
      vdata[index+0].u = tile->u/512.0f;
      vdata[index+0].v = tile->v/512.0f;
      vdata[index+1].x = tile->x+tile->w;
      vdata[index+1].y = tile->y;
      vdata[index+1].u = (tile->u+tile->uw)/512.0f;
      vdata[index+1].v = tile->v/512.0f;
      vdata[index+2].x = tile->x+tile->w;
      vdata[index+2].y = tile->y+tile->h;
      vdata[index+2].u = (tile->u+tile->uw)/512.0f;
      vdata[index+2].v = (tile->v+tile->vh)/512.0f;
      vdata[index+3].x = tile->x;
      vdata[index+3].y = tile->y+tile->h;
      vdata[index+3].u = tile->u/512.0f;
      vdata[index+3].v = (tile->v+tile->vh)/512.0f;
      index+=4;
      tile_index++;
    }
  vbo->Unlock();

  /*index=0;
  unsigned short* idata = ibo->Lock();
  for (int i=0;i<width_-1;++i)
    for (int j=0;j<height_-1;++j) {
      idata[index+0] = (j*width_)+i;
      idata[index+1] = (j*width_)+i+1;
      idata[index+2] = ((j+1)*width_)+i+1;
      idata[index+3] = ((j+1)*width_)+i;
      index+=4;
    }
  ibo->Unlock();*/
  

/*}

void TileSet::Deinitialize() {
  //delete [] tile_list;
  //delete ibo;
  //delete vbo;
}

*/



}