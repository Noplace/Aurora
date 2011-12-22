#include "../aurora.h"

namespace aurora {
namespace resource {

bool TextureResource::Load() {
  if (loaded_ == true) 
    return false;

  int res = Resource::ReadWholeFile();
  if (res == S_OK) {
    auto gfx = &manager_->engine()->gfx_context();
    //res = D3DX11CreateShaderResourceViewFromMemory(manager_->engine()->gfx_context().device(),data_pointer,data_length,NULL,NULL,&srv_,NULL);
    //res = D3DX11CreateTextureFromMemory(manager_->engine()->gfx_context().device(),data_pointer,data_length,NULL,NULL,&texture_,NULL);
    res = gfx->CreateTextureFromMemory(data_pointer,data_length,texture_);
    if (res == S_OK) {
      gfx->CreateResourceView(texture_,srv_);
    }

    Resource::DeallocateMemory();
    if (res == S_OK) {
      loaded_ = true;
      return true;
    }
  }
  return false;
}

bool TextureResource::Unload() {
  if (loaded_ == false) 
    return false;
  manager_->engine()->gfx_context().DestroyResourceView(srv_);
  manager_->engine()->gfx_context().DestroyTexture(texture_);
  loaded_ = false;
  return S_OK;
}

}
}