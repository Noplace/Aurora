#include "state_manager.h"
#include "../engine.h"

namespace aurora {

int StateManager::AddState(State* state)  {
  if (GetStateById(state->id()) == NULL) {
    state->set_engine(engine_);
    state->set_state_manager(this);
    states.push_back(state);
    return 0;
  } else {
    return -1;
  }
}

int StateManager::RemoveState(int id) {
  
  for(StateVector::size_type i = 0; i < states.size(); ++i) {
    if (states[i]->id() == id) {
      states[i] = states.back();
      states.pop_back();
      return 0;
    }
  }
  return -1;
}

State* StateManager::GetStateById(int id) {
  
  for(StateVector::iterator i = states.begin(); i != states.end(); ++i) {
    if ((*i)->id() == id) {
      return *i;
    }
  }
  return NULL;
}

int StateManager::ChangeState(int id) {
  if (current_state_ != NULL) {
    current_state_->OnStateExit();
  }
  current_state_ = GetStateById(id);
  current_state_->set_start_time(engine_->total_cycles());
  current_state_->OnStateEnter();
  return 0;
}

}