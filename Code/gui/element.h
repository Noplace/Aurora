#ifndef AURORA_GUI_ELEMENT_H
#define AURORA_GUI_ELEMENT_H

#include <VisualEssence/Code/context/context.h>
#include <VisualEssence/Code/font/writer.h>

namespace aurora {
namespace gui {

class Element : public graphics::shape::Shape {
 public:
  Element() {}
  ~Element() { }
  acGraphics::Font* font() { return font_; }
  void set_font(acGraphics::Font* font) { 
    font_ = font;
  }
 protected:
  acGraphics::Font* font_;
  graphics::font::Writer writer_;
};

}
}

#endif