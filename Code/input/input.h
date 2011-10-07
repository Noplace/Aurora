#ifndef AURORA_INPUT_INPUT_H
#define AURORA_INPUT_INPUT_H

#include "controller.h"
#include "xbox360_controller.h"

namespace aurora {
namespace input {

class Input {
 public:
  Input();
  ~Input();
  void Poll();
  Xbox360Controller controller1;
};

}
}

#endif