#ifndef AURORA_RESOURCE_TEXTURE_RESOURCE_H
#define AURORA_RESOURCE_TEXTURE_RESOURCE_H

//#include <D3DX11.h>
#include "resource.h"

namespace aurora {
namespace resource {

class ResourceManager;

class TextureResource : public Resource {
 public:
  TextureResource() : Resource() { /*memset(&info_,0,sizeof(info_));*/ }
  virtual ~TextureResource()  {}
  virtual bool Load();
  virtual bool Unload();
  ID3D11ShaderResourceView* srv() { return static_cast<ID3D11ShaderResourceView*>(srv_.data_pointer); }
  ID3D11Resource* texture() { return static_cast<ID3D11Resource*>(texture_.data_pointer); }
 protected:
  ve::ResourceView srv_;
  ve::Texture texture_;
  //D3DX11_IMAGE_LOAD_INFO info_;

};

}
}
#endif
