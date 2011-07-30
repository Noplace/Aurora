#include "../engine.h"
#include "font_resource.h"

namespace game_engine {
namespace resource {

bool FontResource::Load() {
  if (loaded_ == true) 
    return false;
  acGraphics::FontLoaderBinaryFormat font_loader(filename());
  font_ = font_loader.GenerateFont();
  loaded_ = true;
  return true;
}

bool FontResource::Unload() {
  if (loaded_ == false) 
    return false;
  delete font_;
  loaded_ = false;
  return true;
}

}
}