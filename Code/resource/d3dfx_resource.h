#ifndef GAME_ENGINE_RESOURCE_EFFECT_RESOURCE_H
#define GAME_ENGINE_RESOURCE_EFFECT_RESOURCE_H

#include <d3dx11.h>
#include "resource.h"

namespace game_engine {
namespace resource {

class ResourceManager;

class D3DFXResource : public Resource {
 public:
  D3DFXResource() : Resource() { }
  virtual ~D3DFXResource()  {}
  virtual bool Load();
  virtual bool Unload();
  ID3DX11Effect*  effect() { return effect_; }
 protected:
  ID3DX11Effect* effect_;
};

}
}
#endif