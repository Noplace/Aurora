#include "aurora.h"

namespace aurora {

int GameView::Initialize(Engine* engine) {
  int hr = S_OK;
  set_engine(engine);
  hr = camera_.Initialize(&engine->gfx_context());
  return hr;
}

int GameView::Deinitialize() {
  int hr = S_OK;
  hr = camera_.Deinitialize();
  return hr;
}

}