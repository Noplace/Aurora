#ifndef GAME_ENGINE_RESOURCE_TEXTURE_RESOURCE_H
#define GAME_ENGINE_RESOURCE_TEXTURE_RESOURCE_H

#include <D3DX11.h>
#include "resource.h"

namespace game_engine {
namespace resource {

class ResourceManager;

class TextureResource : public Resource {
 public:
  TextureResource() : Resource() , srv_(NULL) { memset(&info_,0,sizeof(info_)); }
  virtual ~TextureResource()  {}
  virtual bool Load();
  virtual bool Unload();
  ID3D11ShaderResourceView* srv() { return srv_; }
  ID3D11Resource* texture() { return texture_; }
 protected:
  ID3D11ShaderResourceView* srv_;
  ID3D11Resource* texture_;
  D3DX11_IMAGE_LOAD_INFO info_;

};

}
}
#endif
