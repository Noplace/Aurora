#ifndef AURORA_RESOURCE_EFFECT_RESOURCE_H
#define AURORA_RESOURCE_EFFECT_RESOURCE_H

namespace aurora {
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