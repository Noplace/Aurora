#ifndef AURORA_ANIMATION_CUBIC_MOTION_H
#define AURORA_ANIMATION_CUBIC_MOTION_H

#include "tween.h"

namespace aurora {
namespace animation {

class Context;

class CubicMotion : public Tween {
 public:
  void Process(DefaultTimeType delta);
  CubicMotion& set_from(float from) { from_ = from; return *this; }
  CubicMotion& set_to(float to) { to_ = to; return *this; }
 private:
  float from_;
  float to_;
};

}
}

#endif