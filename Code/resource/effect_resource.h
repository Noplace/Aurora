#ifndef GAME_ENGINE_RESOURCE_EFFECT_RESOURCE_H
#define GAME_ENGINE_RESOURCE_EFFECT_RESOURCE_H

#include <VisualEssence/Code/effect/effect.h>
#include "resource.h"

namespace game_engine {
namespace resource {

class ResourceManager;

class EffectResource : public Resource {
 public:
  EffectResource() : Resource() { }
  virtual ~EffectResource()  {}
  virtual bool Load();
  virtual bool Unload();
  graphics::Effect* effect() { return effect_; }
 protected:
  graphics::Effect* effect_;
};

}
}
#endif