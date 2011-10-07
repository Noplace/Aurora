#ifndef AURORA_GUI_MENU_H
#define AURORA_GUI_MENU_H

namespace aurora {
namespace gui {

class Menu : public Element {
 public:
  Menu() : item_count(0),selected_index(0) {}
  virtual ~Menu() {}
  int Construct();
  int BuildTransform();
  int Draw();
  void AddItem(char* caption);
 protected:
  struct Item {
    char caption[255];
    int index;
    bool selected;
  };
  Item list_[10];
  int item_count;
  int selected_index;
};

}
}

#endif