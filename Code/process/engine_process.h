#ifndef AURORA_PROCESS_ENGINE_PROCESS_H
#define AURORA_PROCESS_ENGINE_PROCESS_H

#include <WinCore/process/process.h>

namespace aurora {
class Engine;
}

namespace aurora {
namespace process {

class EngineProcess : public core::Process {
 public:
  EngineProcess() {}
  virtual ~EngineProcess() {}
  void set_engine(Engine* engine) {
    engine_ = engine;
  }
 protected:
   Engine* engine_;
};

}
}

#endif