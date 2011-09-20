#ifndef AURORA_ANIMATION_SINE_WAVE_H
#define AURORA_ANIMATION_SINE_WAVE_H

namespace aurora {
namespace animation {

class Context;


class SineWave : public Tween {
 public:
  void Process(DefaultTimeType delta);
  void set_amplitude(float amp) { amp_ = amp; }
  void set_frequency(float freq) { freq_ = freq; }
 private:
  float amp_;
  float freq_;
};

}
}

#endif