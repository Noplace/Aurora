#include "element.h"
#include "menu.h"

namespace aurora {
namespace gui {

int Menu::Construct() {
  writer_.Initialize(context_);
  writer_.PrepareWrite(512);
  return 0;
}

int Menu::BuildTransform() {
  return Shape::BuildTransform();
}

int Menu::Draw() {
  return 0;
}

void Menu::AddItem(char* caption) {
  strcpy(list_[item_count].caption,caption);
   // writer_.PrepareWrite(512);
  //writer_.WriteBox(list_[item_count].caption,
  //copy vertices
  item_count++;
}

}
}