#ifndef GAME_ENGINE_RESOURCE_FONT_RESOURCE_H
#define GAME_ENGINE_RESOURCE_FONT_RESOURCE_H

#include <VisualEssence/Code/font/bmfont/font_loader.h>
#include "resource.h"

namespace game_engine {
namespace resource {

class ResourceManager;

class FontResource : public Resource {
 public:
  FontResource() : Resource()  { }
  virtual ~FontResource()  {}
  virtual bool Load();
  virtual bool Unload();
  acGraphics::Font* font() { return font_; }
 protected:
  acGraphics::Font* font_;
};

}
}
#endif