#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H


namespace aurora {

typedef std::vector<State*> StateVector;

class StateManager : public GameView {
 public:
  StateManager() : current_state_(NULL) {  }
  virtual ~StateManager() { }
  virtual int Initialize(Engine* engine);
  virtual int Deinitialize();
  virtual int AddState(State*);
  virtual int RemoveState(int id);
  virtual State* GetStateById(int id);
  virtual int ChangeState(int id);
  virtual State* current_state() { return current_state_; }
  virtual void Input();
  virtual void Update(float dt);
  virtual void Interpolate(float dt);
  virtual void Draw();
 private:
  StateVector states;
  State* current_state_;
};

}

#endif