#ifndef GAME_ENGINE_OBJECT_H
#define GAME_ENGINE_OBJECT_H

#include <WinCore/types.h>

namespace game_engine {

class Engine;

class Component {
 public:
  Component() : engine_(0), start_time_(0ULL) { }
  Engine* engine() { return engine_; }
  void set_engine(Engine* engine) { engine_ = engine; }
  uint64_t start_time() { return start_time_; }
  void set_start_time(uint64_t start_time) { start_time_ = start_time; }
  uint64_t local_time();
  uint64_t global_time();
 protected:
  Engine* engine_;
  uint64_t start_time_;
};

}
#endif