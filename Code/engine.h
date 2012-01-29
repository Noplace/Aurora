#ifndef AURORA_ENGINE_H
#define AURORA_ENGINE_H

namespace aurora {

class Engine {
 public:
  core::LogManager log;
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
  graphics::Context& gfx_context() { return *gfx_context_; }
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
  graphics::Context* gfx_context_;
  input::Input input_;
  core::ProcessManager process_manager_;
  struct {
    uint64_t current_cycles;
    uint64_t prev_cycles;
    uint64_t total_cycles;
    uint32_t fps_counter;
    uint32_t ups_counter;
    uint32_t fps;
    uint32_t ups;
    float render_time_span;
    float fps_time_span;
    float span_accumulator;

  } timing;

};

}

#endif