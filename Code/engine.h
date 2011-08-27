#ifndef AURORA_ENGINE_H
#define AURORA_ENGINE_H

#include <WinCore/windows/windows.h>
#include <WinCore/timer/timer2.h>
#include <WinCore/animation/animation.h>
#include <WinCore/process/process_manager.h>
#include <VisualEssence/Code/context/contextd3d11.h>
//#include <Graphics/vertex.h>
#include <VisualEssence/Code/buffer/vertex_buffer.h>
#include <VisualEssence/Code/camera/camera2d.h>
#include <VisualEssence/Code/sprite/sprite.h>
//#include <Graphics/font/bmfont/font.h>
#include <VisualEssence/Code/effect/effect.h>
#include <VisualEssence/Code/font/writer.h>
#include "component.h"
#include "resource/resource_manager.h"


namespace aurora {

class GameView;

class Engine {
 public:
  Engine();
  ~Engine();
  int Initialize();
  int Deinitialize();
  void Loop();
  aurora::resource::ResourceManager resource_manager;
  utilities::Timer* timer() { return timer_; }
  void set_timer(utilities::Timer* timer) { timer_ = timer; }
  core::windows::Window* window() { return window_; }
  void set_window(core::windows::Window* window) { window_ = window; }
  core::animation::Context& animation() { return animation_; }
  graphics::ContextD3D11& gfx_context() { return gfx_context_; }
  uint64_t total_cycles() { return timing.total_cycles; }
  float total_time() { return timing.total_cycles * timer_->resolution(); }
  GameView* current_scene;
  core::ProcessManager& process_manager() { return process_manager_; }
  uint32_t fps() { return timing.fps; }
 private:
  utilities::Timer* timer_;
  core::windows::Window* window_;
  core::animation::Context animation_;
  graphics::ContextD3D11 gfx_context_;
  
  core::ProcessManager process_manager_;
  struct {
    uint64_t current_cycles;
    uint64_t prev_cycles;
    uint64_t total_cycles;
    uint32_t fps_counter;
    uint32_t fps;
    float render_time_span;
    float fps_time_span;
  } timing;

};

}

#endif