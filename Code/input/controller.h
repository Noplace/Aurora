#ifndef AURORA_INPUT_CONTROLLER_H
#define AURORA_INPUT_CONTROLLER_H

namespace aurora {
namespace input {

class Controller {
 public:
  bool enabled() { return enabled_; }
  virtual bool A() = 0;
  virtual bool B() = 0;
  virtual bool X() = 0;
  virtual bool Y() = 0;
  virtual bool Up() = 0;
  virtual bool Down() = 0;
  virtual bool Left() = 0;
  virtual bool Right() = 0;
  virtual bool Start() = 0;
  virtual bool Select() = 0;
  virtual float LeftTrigger() = 0;
  virtual float RightTrigger() = 0;
  virtual float LeftThumbDirection() = 0;
  virtual float LeftThumbMagnitude() = 0;
  virtual float RightThumbDirection() = 0;
  virtual float RightThumbMagnitude() = 0;
  virtual void Handle(void* data) = 0;
  void AssignIndex(int index) {
    index_ = index;
  }
 protected:
  int index_;
  bool enabled_;

};

}
}

#endif