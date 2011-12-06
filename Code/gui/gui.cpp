#include "../aurora.h"
#include "gui.h"

namespace aurora {
namespace gui {

void Gui::AddElement(Element* element) {
  element->Initialize(&engine_->gfx_context());
  element->Construct();
  elements_.push_back(element);
}

void Gui::Initialize() {

}

void Gui::Update(float dt) {
  for (unsigned int i=0;i<elements_.size();++i) {
    // if required
    elements_[i]->BuildTransform();
  }
}

void Gui::Uninitialize() {
  for (unsigned int i=0;i<elements_.size();++i) {
    elements_[i]->Deinitialize();
  }
}

void Gui::Draw() {
  for (unsigned int i=0;i<elements_.size();++i) {
    elements_[i]->Draw();
  }
}

}
}