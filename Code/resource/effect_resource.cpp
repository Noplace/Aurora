#include "../engine.h"
#include "effect_resource.h"

namespace aurora {
namespace resource {

bool EffectResource::Load() {
  if (loaded_ == true) 
    return false;

  if (Resource::ReadWholeFile() != S_OK)
    return false;
  effect_ = new graphics::Effect();
  if (effect_->Initialize(&manager_->engine()->gfx_context()) != S_OK)
    return false;
  if (effect_->CreateFromMemory(data_pointer,data_length) != S_OK)
    return false;

  loaded_ = true;
  return true;
}

bool EffectResource::Unload() {
  if (loaded_ == false) 
    return false;
  if (effect_->Deinitialize() != S_OK)
    return false;
  delete effect_;
  loaded_ = false;
  return true;
}

}
}