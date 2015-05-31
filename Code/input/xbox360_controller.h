#ifndef AURORA_INPUT_XBOX360_CONTROLLER_H
#define AURORA_INPUT_XBOX360_CONTROLLER_H


namespace aurora {
namespace input {

class Xbox360Controller : public Controller {
 public:
  Xbox360Controller();
  ~Xbox360Controller();
  bool A();
  bool B();
  bool X();
  bool Y();
  bool Up();
  bool Down();
  bool Left();
  bool Right();
  bool Start();
  bool Select();
  float LeftTrigger();
  float RightTrigger();
  float LeftThumbDirection();
  float LeftThumbMagnitude();
  float RightThumbDirection();
  float RightThumbMagnitude();
  void Handle(void* data);
 protected:
  float CalculateMagnitude(int16_t x, int16_t y);
  float CalculateDirection(int16_t x, int16_t y);
  struct State {
    uint16_t  buttons;
    uint8_t   left_trigger;
    uint8_t   right_trigger;
    int16_t  thumb_lx;
    int16_t  thumb_ly;
    int16_t  thumb_rx;
    int16_t  thumb_ry;
  } state, last_state;
};

}
}

#endif