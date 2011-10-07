#ifndef AURORA_ENGINE_H
#define AURORA_ENGINE_H

#include <WinCore/windows/windows.h>
#include <WinCore/timer/timer2.h>
#include <WinCore/process/process_manager.h>
#include <VisualEssence/Code/context/contextd3d11.h>
#include <VisualEssence/Code/camera/camera2d.h>
#include <VisualEssence/Code/sprite/sprite.h>
#include <VisualEssence/Code/effect/effect.h>
#include <VisualEssence/Code/font/writer.h>
#include "component.h"
#include "animation/animation.h"
#include "resource/resource_manager.h"
#include "input/input.h"
#include "process/engine_process.h"
#include "gui/gui.h"

namespace aurora {

class GameView;

class Engine {
 public:
  Engine();
  ~Engine();
  int Initialize();
  int Deinitialize();
  void Loop();
  void HandleWindowMessages(HWND window_handle, UINT message, WPARAM wparam, LPARAM lparam);
  aurora::resource::ResourceManager resource_manager;
  utilities::Timer* timer() { return timer_; }
  void set_timer(utilities::Timer* timer) { timer_ = timer; }
  core::windows::Window* window() { return window_; }
  void set_window(core::windows::Window* window) { window_ = window; }
  animation::AnimationProcess& animation() { return animation_; }
  graphics::ContextD3D11& gfx_context() { return gfx_context_; }
  uint64_t total_cycles() { return timing.total_cycles; }
  float total_time() { return timing.total_cycles * timer_->resolution(); }
  GameView* current_scene;
  core::ProcessManager& process_manager() { return process_manager_; }
  input::Input& input() { return input_; }
  uint32_t fps() { return timing.fps; }
 private:
  utilities::Timer* timer_;
  core::windows::Window* window_;
  animation::AnimationProcess animation_;
  graphics::ContextD3D11 gfx_context_;
  input::Input input_;
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