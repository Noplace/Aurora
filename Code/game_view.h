#ifndef AURORA_SCENE_H
#define AURORA_SCENE_H

#include <VisualEssence/Code/component.h>
#include <VisualEssence/Code/camera/camera.h>
#include <VisualEssence/Code/shader/shader.h>

namespace aurora {

class GameView : public EngineComponent {
 public:
  GameView() { }
  virtual ~GameView() { }
  virtual int Initialize(Engine* engine);
  virtual int Deinitialize();
  virtual void UpdatePhysics(float) = 0;
  virtual void Update(float) = 0;
  virtual void Draw() = 0;
 protected:

  graphics::Camera camera_;
};


}

#endif