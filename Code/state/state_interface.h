#ifndef GAME_STATE_INTERFACE_H
#define GAME_STATE_INTERFACE_H

#include "../engine_component.h"

namespace aurora {

class StateInterface : public EngineComponent {
 public:
  virtual void OnInput() = 0;
  virtual void OnUpdate(float) = 0;
  virtual void OnInterpolate(float) = 0;
  virtual void OnDraw() = 0;
  virtual void OnStateEnter() = 0;
  virtual void OnStateExit() = 0;
 protected:
  StateInterface() {  } 
};

}

#endif