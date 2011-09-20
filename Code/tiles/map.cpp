#include <VisualEssence/Code/context/context.h>
#include "tile_set.h"
#include "layer.h"
#include "map.h"

namespace aurora {
namespace tiles {

int Map::Initialize(graphics::Context* context, int width, int height, int tile_width, int tile_height) {
  graphics::Component::Initialize(context);
  width_ = width;
  height_ = height;
  tile_width_ = tile_width;
  tile_height_ = tile_height;
  layer_count_ = 0;


  return S_OK;
}

int Map::Deinitialize() {

  context_->DestroyBuffer(vertex_buffer_);
  layer_count_ = 0;
  {
    std::vector<Layer*>::iterator i;

    for(i = layers.begin(); i != layers.end(); i++) {
      Layer* layer = (*i);
      layer->Deinitialize();
      delete layer;
    }
  }
  {
    std::vector<TileSet*>::iterator i;

    for(i = tilesets.begin(); i != tilesets.end(); i++) {
      TileSet* tileset = (*i);
      delete tileset;
    }
  }

  return S_OK;
}

int Map::AddLayer() {
  Layer* layer = new Layer();
  layer->set_index(-layer_count_);
  layers.push_back(layer);
  return layer_count_++;
}

int Map::Construct() {


  vertex_buffer_.description.bind_flags = D3D11_BIND_VERTEX_BUFFER;
  vertex_buffer_.description.usage = D3D11_USAGE_DEFAULT;
  vertex_buffer_.description.byte_width = sizeof( graphics::shape::Vertex ) * width_ * height_ * 4 * layer_count_;
  vertex_buffer_.description.cpu_access_flags = 0;
  context_->DestroyBuffer(vertex_buffer_);
  context_->CreateBuffer(vertex_buffer_,NULL);

  for (int i=0;i<layer_count_;++i) {
    layers[i]->Initialize(this,width_,height_,tile_width_,tile_height_);
    layers[i]->set_buffer_offset(buffer_offset(i));
    layers[i]->Construct();
  }

  return S_OK;
}

int Map:: BuildTransform() {
  world_ = XMMatrixTransformation2D(XMLoadFloat2(&XMFLOAT2(0,0)),
    0,
    XMLoadFloat2(&XMFLOAT2(scale_,scale_)),
    XMLoadFloat2(&XMFLOAT2(0,0)),
    angle_,
    XMLoadFloat2(&XMFLOAT2(x_,y_)));
  world_._43 = z_;
  return S_OK;
}

int Map::Draw() {

  for (int i=0;i<layer_count_;++i) {
    layers[i]->Draw();
  }

  return S_OK;
  /*glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(-left,-right,0);

  glBindTexture(GL_TEXTURE_2D,tilesets[0]->texture_->handle());

  layers[0]->vbo->Bind();

  //ibo->Bind();
  glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(gl_c4ub_v2f), 0);
  glVertexPointer(2, GL_FLOAT, sizeof(gl_c4ub_v2f), (GLvoid*)(4));
  glTexCoordPointer(2,GL_FLOAT, sizeof(gl_c4ub_v2f), (GLvoid*)(12));

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  //glEnableClientState(GL_INDEX_ARRAY);

  glDrawArrays(GL_QUADS,0,(layers[0]->width_)*(layers[0]->height_)*4);
  //glDrawElements(GL_QUADS,(width_-1)*(height_-1)*4,GL_UNSIGNED_SHORT,0);
  //glDrawRangeElements(GL_QUADS,0,4,16,GL_UNSIGNED_SHORT,0);

  //glDisableClientState(GL_INDEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glPopMatrix();*/

}



}
}