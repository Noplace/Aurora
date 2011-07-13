#ifndef GAME_STATE_INTERFACE_H
#define GAME_STATE_INTERFACE_H

#include "../component.h"

namespace game_engine {

class StateInterface : public Component {
 public:
  virtual void OnInput() = 0;
  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;
  virtual void OnStateEnter() = 0;
  virtual void OnStateExit() = 0;
 protected:
  StateInterface() {  } 
};

}

#endif