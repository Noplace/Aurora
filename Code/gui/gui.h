#ifndef AURORA_GUI_GUI_H
#define AURORA_GUI_GUI_H

#include <vector>
#include <VisualEssence/Code/context/context.h>
#include "../process/engine_process.h"
#include "element.h"

namespace aurora {
namespace gui {

class Gui : public aurora::process::EngineProcess {
 public:
  Gui() {}
  ~Gui() {}
  void AddElement(Element* element);
  void Initialize();
  void Update(float dt);
  void Uninitialize();
  void Draw();
 private:
  std::vector<Element*> elements_;
};

}
}

#endif