
#ifndef CORE_ANIMATION_CUSTOM_H
#define CORE_ANIMATION_CUSTOM_H

namespace aurora {
namespace animation {

class Custom : public  aurora::animation::Tween {
 public:
  std::function<void(float,float,float)> fn;

  template<class Func>
  Custom& set_function(Func& fn) {
    this->fn = fn;
    return *this;
  }
  void Process(float delta) {
    fn(delta,current_play_time_,max_time_);
  }
};

}
}

#endif