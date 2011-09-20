#include <VisualEssence/Code/context/context.h>
#include "tile_set.h"
#include "map.h"
#include "layer.h"

namespace aurora {
namespace tiles {


int Layer::Initialize(Map* map, int width, int height, int tile_width, int tile_height) {
  map_ = map;
  width_ = width;
  height_ = height;
  tile_width_ = tile_width;
  tile_height_ = tile_height;
  vertex_count_ = width_ * height_ * 4;
  return S_OK;
}

int Layer::Deinitialize() {

  return S_OK;
}


graphics::shape::Vertex* Layer::CreateVertices() {

  graphics::shape::Vertex* vertices = new graphics::shape::Vertex[vertex_count_];

  graphics::shape::Vertex* curr = &vertices[0];
  XMFLOAT4 color =  XMFLOAT4(1,0,1,1);
  for (int i=0;i<height_-1;++i) {
    for (int j=0;j<width_-1;++j) {
      curr->pos = XMFLOAT3(j*tile_width_,i*tile_height_,index_);
      curr->color = color;
      ++curr;
      curr->pos = XMFLOAT3((j+1)*tile_width_,i*tile_height_,index_);
      curr->color = color;
      ++curr;
      curr->pos = XMFLOAT3(j*tile_width_,(i+1)*tile_height_,index_);
      curr->color = color;
      ++curr;
      curr->pos = XMFLOAT3((j+1)*tile_width_,(i+1)*tile_height_,index_);
      curr->color = color;
      ++curr;
    }
  }
  
  return vertices;
}

int Layer::Construct() {
  graphics::shape::Vertex* vertices = CreateVertices();
  if (!vertices)
    return S_FALSE;

  graphics::Context* context = map_->context();

  int hr = context->CopyToVertexBuffer(map_->vertex_buffer(),vertices,sizeof(graphics::shape::Vertex),buffer_offset_,vertex_count_);
  delete [] vertices;

  return S_OK;
}

int Layer::Draw() {
  UINT stride = sizeof( graphics::shape::Vertex );
  UINT offset = buffer_offset_;
  graphics::Context* context = map_->context();
  context->SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );
  context->SetVertexBuffers(0,1,&map_->vertex_buffer(),&stride,&offset);
  return context->Draw(vertex_count_,0);
}

}
}