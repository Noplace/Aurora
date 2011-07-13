#include "../engine.h"
#include "texture_resource.h"

namespace game_engine {
namespace resource {

bool TextureResource::Load() {
  bool res = Resource::Load();
  if (res) {
    HRESULT hr = D3DX11CreateShaderResourceViewFromMemory(manager_->engine()->gfx_context().device(),data_pointer,data_length,NULL,NULL,&srv_,NULL);
  }
  return res;
}

bool TextureResource::Unload() {
  bool res = Resource::Unload();
  if (res) {
    if (srv_ != NULL) {
        srv_->Release();
        srv_ = NULL;
    }
  }
  return res;
}

}
}