#ifndef AURORA_SCENE_H
#define AURORA_SCENE_H


namespace aurora {

class GameView : public EngineComponent {
 public:
  GameView() { }
  virtual ~GameView() { }
  virtual int Initialize(Engine* engine);
  virtual int Deinitialize();
  virtual void Input() = 0;
  virtual void Update(float) = 0;
  virtual void Interpolate(float) = 0;
  virtual void Draw() = 0;
 protected:

  graphics::Camera camera_;
};


}

#endif