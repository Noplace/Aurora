#include "../aurora.h"
#include "font_resource.h"

namespace aurora {
namespace resource {
  
bool FontResource::Load() {
  if (loaded_ == true) 
    return false;
  acGraphics::FontLoaderBinaryFormat font_loader(filepath());
  font_loader.Initialize(&manager_->engine()->gfx_context());
  font_loader.LoadFont(&font_);
  font_loader.Deinitialize();
  loaded_ = true;
  return true;
}

bool FontResource::Unload() {
  if (loaded_ == false) 
    return false;
  loaded_ = false;
  return true;
}

}
}