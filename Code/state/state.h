#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stdlib.h>
#include "state_interface.h"

namespace game_engine {

class StateManager;

class State : public StateInterface {
 public:
  State() : id_(0),state_manager_(NULL) { };
  State(int id) : id_(id) { };
  virtual void OnInput() { }
  virtual void OnUpdate() { }
  virtual void OnRender() { }
  virtual void OnStateEnter() { }
  virtual void OnStateExit() { }
  int id() { return id_; }
  StateManager* state_manager() { return state_manager_; }
  void set_state_manager(StateManager* state_manager) { state_manager_ = state_manager; }
 protected:
  int id_;
  StateManager* state_manager_;
};

}

#endif