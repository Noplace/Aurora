#include "../engine.h"
#include "font_resource.h"

namespace aurora {
namespace resource {
  
bool FontResource::Load() {
  if (loaded_ == true) 
    return false;
  acGraphics::FontLoaderBinaryFormat font_loader(filename());
  font_loader.Initialize(&manager_->engine()->gfx_context());
  font_ = font_loader.GenerateFont();
  font_loader.Deinitialize();
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