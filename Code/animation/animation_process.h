#ifndef AURORA_ANIMATION_ANIMATION_PROCESS_H
#define AURORA_ANIMATION_ANIMATION_PROCESS_H

namespace aurora {
namespace animation {

class AnimationProcess : public core::Process {
 public:
  AnimationProcess() : core::Process() {}
  ~AnimationProcess() {}
  void Initialize() {
  }
  void Uninitialize() {
  }
  void Update(float dt) {
    TweenVector::iterator i;
    Tween* tween_ptr;
    for (i = tween_list.begin(); i != tween_list.end(); ++i) {
      tween_ptr =  (*i);
      tween_ptr->EncapsulatedProcess(dt);
    }
    //std::remove_if
  }

// private:
  TweenVector tween_list;
};

}
}

#endif