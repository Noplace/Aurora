#ifndef GAME_ENGINE_SCENE_H
#define GAME_ENGINE_SCENE_H

#include <VisualEssence/Code/component.h>
#include <VisualEssence/Code/camera/camera.h>
#include <VisualEssence/Code/shader/shader.h>

namespace game_engine {

class GameView : public Component {
 public:
  GameView() { }
  virtual ~GameView() { }
  virtual int Initialize(Engine* engine) {
    int hr = S_OK;
    set_engine(engine);
    hr = camera_.Initialize(&engine->gfx_context());
    return hr;
  }
  virtual int Deinitialize() {
    int hr = S_OK;
    hr = camera_.Deinitialize();
    return hr;
  }
  virtual void Update(float) = 0;
  virtual void Draw() = 0;
 protected:

  graphics::Camera camera_;
};


}

#endif