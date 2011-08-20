#include "../engine.h"
#include "texture_resource.h"

namespace game_engine {
namespace resource {

bool TextureResource::Load() {
  if (loaded_ == true) 
    return false;

  int res = Resource::ReadWholeFile();
  if (res == S_OK) {
    //res = D3DX11CreateShaderResourceViewFromMemory(manager_->engine()->gfx_context().device(),data_pointer,data_length,NULL,NULL,&srv_,NULL);
    res = D3DX11CreateTextureFromMemory(manager_->engine()->gfx_context().device(),data_pointer,data_length,NULL,NULL,&texture_,NULL);

    if (res == S_OK) {
      manager_->engine()->gfx_context().device()->CreateShaderResourceView(texture_,NULL,&srv_);
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

  SafeRelease(&srv_);
  SafeRelease(&texture_);
  loaded_ = false;
  return S_OK;
}

}
}