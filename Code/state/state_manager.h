#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H


#include <vector>
#include "../component.h"
#include "state.h"

namespace aurora {

typedef std::vector<State*> StateVector;

class StateManager : public Component {
 public:
  StateManager() : current_state_(NULL) {  }
  int AddState(State*);
  int RemoveState(int id);
  State* GetStateById(int id);
  int ChangeState(int id);
  State* current_state() { return current_state_; }
 private:
  StateVector states;
  State* current_state_;
};

}

#endif